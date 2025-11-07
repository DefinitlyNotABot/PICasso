#pragma once

#include "../instruction.hpp"

class SUBWF : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   SUBWF(uint16_t instruction);
 void execute(); 
};
