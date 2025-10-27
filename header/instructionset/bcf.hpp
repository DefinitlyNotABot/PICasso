#pragma once

#include "../instruction.hpp"

class BCF   : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BCF(uint16_t instruction);
 void execute(); 
};
