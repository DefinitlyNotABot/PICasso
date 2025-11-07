#pragma once

#include "../instruction.hpp"

class RETFIE: public Instruction 
{
 public:
    RETFIE(uint16_t instruction);
 void execute(); 
};
