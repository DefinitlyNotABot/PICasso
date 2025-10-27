#pragma once

#include "../instruction.hpp"

class MOVLW : public Instruction 
{
   uint16_t file;
 public:
   MOVLW(uint16_t instruction);
 void execute(); 
};
