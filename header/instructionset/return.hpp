#pragma once

#include "../instruction.hpp"

class RETURN: public Instruction 
{
 public:
    RETURN(uint16_t instruction);
 void execute(); 
};
