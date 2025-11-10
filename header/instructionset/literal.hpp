#pragma once

#include "instruction.hpp"

class Literal : public virtual Instruction 
{ 
    protected:
        uint16_t literal;
};
