#pragma once

#include "../instruction.hpp"

class IORWF : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
   IORWF(uint16_t instruction);
 void execute(); 
};
