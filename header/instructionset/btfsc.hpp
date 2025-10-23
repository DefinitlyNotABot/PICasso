#pragma once

#include "../instruction.hpp"

class BTFSC : public Instruction 
{
   uint8_t bit;
   uint16_t file;
 public:
   BTFSC(uint8_t bit, uint16_t file);
 void execute(); 
};
