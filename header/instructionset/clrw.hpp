#pragma once

#include "../instruction.hpp"

class CLRW  : public Instruction 
{
 public:
    CLRW(uint16_t instruction);
    void execute(); 
};
