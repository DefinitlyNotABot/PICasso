#pragma once

#include "instruction.hpp"

class NOP   : public Instruction 
{
 public:
    NOP(uint16_t instruction);
    uint16_t execute(); 
};
