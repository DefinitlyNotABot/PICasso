#pragma once

#include "../instruction.hpp"

class XORLW : public Instruction 
{
    private:
      uint16_t literal;
   public:
   XORLW(uint16_t instruction);
 void execute(); 
};
