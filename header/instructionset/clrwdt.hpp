#pragma once

#include "../instruction.hpp"

class CLRWDT: public Instruction 
{
 public:
    CLRWDT(uint16_t instruction);
 void execute(); 
};
