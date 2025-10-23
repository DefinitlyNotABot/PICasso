#pragma once

#include "../instruction.hpp"

class ANDLW : public Instruction 
{
   private:
      uint16_t literal;
   public:
   ANDLW(uint16_t literal);
 void execute(); 
};
