#pragma once

#include "../instruction.hpp"

class XORWF : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   XORWF(uint16_t instruction);
 void execute(); 
};
