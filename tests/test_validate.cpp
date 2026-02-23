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
                REQUIRE(pic.readRegister(addr) == to_int(expectedValue));
            } 
            else {
                FAIL("Unknown register in test: " + reg);
            }
        }
    }
}

TEST_CASE("Test all progs", "[validate]") {
    // find all json files in the progs directory
    std::vector<std::string> testFiles;
    for (const auto& entry : std::filesystem::directory_iterator("progs")) {
        if (entry.path().extension() == ".json") {
            testFiles.push_back(entry.path().string());
        }
    }
    // Logger::consoleOutput = Logger::ConsoleOutput::DISABLED;
    Logger::disableLogger("Compiler");
    for (const auto& testFile : testFiles) {
        PIC pic;
        std::string lstFile = testFile.substr(0, testFile.size() - 5) + ".LST"; // replace .json with .LST
        std::cout << "Running test: " << testFile << " with program: " << lstFile << std::endl;
        pic.loadProgram(lstFile);

        std::ifstream jsonFile(testFile);
        REQUIRE(jsonFile.is_open());
        PicTest test = loadTest(testFile);

        runTest(pic, test);
    }
}

