#pragma once

#include "../instruction.hpp"

class GOTO  : public Instruction 
{
   uint16_t address;
 public:
   GOTO(uint16_t address);
 void execute(); 
};
