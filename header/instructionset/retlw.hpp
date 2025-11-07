#pragma once

#include "../instruction.hpp"

class RETLW : public Instruction 
{
   uint16_t file;
 public:
   RETLW(uint16_t instruction);
 void execute(); 
};
