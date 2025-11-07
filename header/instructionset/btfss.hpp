#pragma once

#include "../instruction.hpp"

class BTFSS : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BTFSS(uint16_t instruction);
 void execute(); 
};
