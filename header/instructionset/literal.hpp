#pragma once

#include "instruction.hpp"

class Literal : public Instruction 
{
    protected:
        uint16_t literal;
};
