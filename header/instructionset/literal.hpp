#pragma once

#include "instruction.hpp"

#define SET_ZERO_FLAG_W memoryInterface->writeStatusBit(MemoryInterface::StatusBits::Z, W->readByte() == 0);

class Literal : public virtual Instruction 
{ 
    protected:
        uint16_t literal;
};
