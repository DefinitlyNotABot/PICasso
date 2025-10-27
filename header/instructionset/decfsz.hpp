#pragma once

#include "../instruction.hpp"

class DECFSZ: public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      DECFSZ(uint16_t instruction);
 void execute(); 
};
