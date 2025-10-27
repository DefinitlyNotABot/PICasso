#pragma once

#include "../instruction.hpp"

class BSF   : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BSF(uint16_t instruction);
 void execute(); 
};
