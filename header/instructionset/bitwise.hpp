#pragma once

#include "instruction.hpp"

class Bitwise   : public virtual Instruction 
{  
    protected:
        uint8_t bit;
        uint16_t file;
    public:
};
