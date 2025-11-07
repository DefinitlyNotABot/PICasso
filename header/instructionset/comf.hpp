#pragma once

#include "../instruction.hpp"

class COMF  : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      COMF(uint16_t instruction);
      void execute(); 
};
