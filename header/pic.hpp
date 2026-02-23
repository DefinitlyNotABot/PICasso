#pragma once

#include "memoryInterface.hpp"
#include "alu.hpp"
#include "program.hpp"
#include "register.hpp"

class PIC{
    private:
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
};