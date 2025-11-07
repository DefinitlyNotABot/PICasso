#pragma once

#include "../instruction.hpp"

class BTFSC : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BTFSC(uint16_t instruction);
 void execute(); 
};
