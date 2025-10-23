#pragma once

#include <cstdint>

class Instruction
{
    private:
        uint16_t param1;
        uint16_t param2;
    public:
        virtual void execute() = 0;
};