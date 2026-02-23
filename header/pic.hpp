#pragma once

#include "memoryInterface.hpp"
#include "alu.hpp"
#include "program.hpp"
#include "register.hpp"

class PIC{
    private:
        Logger logger;
        ALU alu;
        Program loadedProgram;
        MemoryInterface memoryInterface;
        Register W;

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
            return W.readByte();
        }
        uint8_t readRegister(uint8_t address) {
            return memoryInterface.readRegister(address);
        }
};