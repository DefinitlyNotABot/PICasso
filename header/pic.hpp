#pragma once

#include "memoryInterface.hpp"
#include "alu.hpp"
#include "program.hpp"
#include "register.hpp"
#include "tui_types.hpp"
#include <array>
#include <mutex>
#include <string>

class PIC{
    private:
        Logger logger;
        ALU alu;
        Program loadedProgram;
        MemoryInterface memoryInterface;
        Register W;
        mutable std::mutex executionMutex;

    public:
        PIC();
        ~PIC();
        void loadProgram(const std::string& program);
        void run();
        void reset();
        void step();
        void printState();
        void printStep(Instruction& instruction);
        uint8_t getProgramCounter();
        uint8_t getStatusBit(char c);
        uint8_t getWRegister(){
            std::lock_guard<std::mutex> lock(executionMutex);
            return W.readByte();
        }
        uint8_t readRegister(uint8_t address) {
            std::lock_guard<std::mutex> lock(executionMutex);
            return memoryInterface.readRegister(address);
        }

        void getSnapshot(PICSnapshot& snapshot);
        bool tryStep(std::string* errorMessage = nullptr);
        bool tryWriteRegister(uint8_t address, uint8_t value, std::string* errorMessage = nullptr);
        bool tryToggleBit(uint8_t address, uint8_t bit, std::string* errorMessage = nullptr);
        bool tryGetInstructionName(uint16_t index, std::string& instructionName, std::string* errorMessage = nullptr);
};