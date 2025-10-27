#pragma once

#include "../instruction.hpp"

class ANDWF : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      ANDWF(uint16_t instruction);
      void execute(); 
};
