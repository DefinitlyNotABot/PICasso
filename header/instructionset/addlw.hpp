#pragma once

#include "../instruction.hpp"

class ADDLW : public Instruction 
{
   private:
      uint16_t literal;
   public:
   ADDLW(uint16_t literal);
 void execute(); 
};
