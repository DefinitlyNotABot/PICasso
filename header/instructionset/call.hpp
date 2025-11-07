#pragma once

#include "../instruction.hpp"

class CALL  : public Instruction 
{
   uint16_t address;
 public:
   CALL(uint16_t instruction);
 void execute(); 
};
