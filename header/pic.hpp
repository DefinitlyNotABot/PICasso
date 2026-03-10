#pragma once

#include <array>
#include <mutex>
#include <string>

#include "memoryInterface.hpp"
#include "alu.hpp"
#include "program.hpp"
#include "register.hpp"
#include "tui_types.hpp"
#include "timer.hpp"

class PIC{
    private:
        Logger logger;
        ALU alu;
        Program loadedProgram;
        Register W;
        Timer timer;

        uint64_t totalSimulatedTimeUs = 0;
        
        std::shared_ptr<MemoryInterface> memoryInterface;
        std::shared_ptr<Prescaler> prescaler;
        
        mutable std::mutex executionMutex;

    public:
        PIC();
        ~PIC();
        void loadProgram(const std::string& program);
        void reset();
        void powerOnReset();
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
            return memoryInterface->readRegister(address);
        }

        void getSnapshot(PICSnapshot& snapshot);
        bool tryStep(std::string* errorMessage = nullptr);
        bool tryWriteRegister(uint8_t address, uint8_t value, std::string* errorMessage = nullptr);
        bool tryWriteRegister(uint8_t address, uint8_t value, bool bank, std::string* errorMessage = nullptr);
        bool tryToggleBit(uint8_t address, uint8_t bit, std::string* errorMessage = nullptr);
        bool tryToggleBit(uint8_t address, uint8_t bit, bool bank, std::string* errorMessage = nullptr);
        bool tryGetInstructionName(uint16_t index, std::string& instructionName, std::string* errorMessage = nullptr);
        uint64_t getSimulatedTimeUs();
};