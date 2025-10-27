#pragma once

#include "../instruction.hpp"

class SWAPF : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   SWAPF(uint16_t instruction);
 void execute(); 
};
