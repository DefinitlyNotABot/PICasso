#include <catch2/catch.hpp>
#include <fstream>

#include "pic.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

struct TestStep {
    std::string pc;
    std::map<std::string, std::string> expected; // Key: Register name, Value: Expected hex/val
};

struct PicTest {
    std::string name;
    std::vector<TestStep> steps;
};

PicTest loadTest(const std::string& filename) {
    std::ifstream file(filename);
    json j;
    file >> j;

    PicTest test;
    test.name = j["test_name"];

    for (auto& step_json : j["steps"]) {
        TestStep step;
        step.pc = step_json["pc"];
        
        for (auto& [key, value] : step_json["expected"].items()) {
            // Store everything as string; convert to int/hex inside your sim logic
            step.expected[key] = value.is_string() ? value.get<std::string>() : std::to_string(value.get<int>());
        }
        test.steps.push_back(step);
    }
    return test;
}

auto to_int = [](const std::string& s, int base = 16) {
    return static_cast<uint8_t>(std::stoul(s.substr(0, s.find_first_not_of("0123456789abcdefABCDEF")), nullptr, base));
};

void runTest(PIC& pic, const PicTest& test) {
    for (const auto& step : test.steps) {
        pic.step(); 

        for (const auto& [reg, expectedValue] : step.expected) {
            if (reg == "W") {
                // Use your to_int helper for "XXh"
                REQUIRE(pic.getWRegister() == to_int(expectedValue));
            } 
            else if (reg == "C") {
                REQUIRE(pic.getStatusBit('C') == std::stoi(expectedValue));
            } 
            else if (reg == "DC") {
                REQUIRE(pic.getStatusBit('D') == std::stoi(expectedValue));
            } 
            else if (reg == "Z") {
                REQUIRE(pic.getStatusBit('Z') == std::stoi(expectedValue));
            } 
            else if (reg == "pc" || reg == "PCL") {
                // Ensure PC is compared numerically
                REQUIRE(pic.getProgramCounter() == to_int(expectedValue));
            } 
            else if (reg.find("ram:") == 0) {
                // Extract address "0C" from "ram:0Ch"
                uint8_t addr = static_cast<uint8_t>(std::stoul(reg.substr(4, 2), nullptr, 16));
                // if(addr == 0) addr = pic.readRegister(0x04); // Handle indirect addressing for FSR
                REQUIRE(pic.readRegister(addr) == to_int(expectedValue));
            } 
            else {
                FAIL("Unknown register in test: " + reg);
            }
        }
    }
}

TEST_CASE("Validate all progs", "[validate]") {
    // Collect files once
    static std::vector<std::string> files = []() {
        std::vector<std::string> f;
        for (const auto& entry : std::filesystem::directory_iterator("progs")) {
            if (entry.path().extension() == ".json") {
                f.push_back(entry.path().string());
            }
        }
        return f;
    }();

    // Use from_range to turn the vector into separate test iterations
    auto const& testFile = GENERATE(from_range(files));

    DYNAMIC_SECTION("File: " << testFile) {
        Logger::disableLogger("Compiler");
        Logger::consoleOutput = Logger::ConsoleOutput::DISABLED;
        PIC pic;
        
        std::string lstFile = testFile.substr(0, testFile.size() - 5) + ".LST";
        pic.loadProgram(lstFile);

        runTest(pic, loadTest(testFile));
    }
}

