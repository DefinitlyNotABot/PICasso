#pragma once

#include "ram.hpp"
#include "alu.hpp"
#include "program.hpp"
#include "register.hpp"

class PIC{
    private:
        ALU alu;
        Program loadedProgram;
        Ram ram;
        Register W;

    public:
        PIC();
        ~PIC();
        void loadProgram(const std::string& program);
        void run();
};