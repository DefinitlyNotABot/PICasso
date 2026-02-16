#pragma once

#include "ram.hpp"
#include "alu.hpp"
#include "program.hpp"

class PIC{
    private:
        ALU alu;
        Program loadedProgram;
        Ram ram;

    public:
        PIC();
        ~PIC();
        void loadProgram(const std::string& program);
        void run();
};