#pragma once

#include "instruction.hpp"

class Jump  : public virtual Instruction 
{
    protected:
        uint16_t address;
    public:

};
