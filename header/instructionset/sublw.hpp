#pragma once

#include "../instruction.hpp"

class SUBLW : public Instruction 
{
   private:
      uint16_t literal;
   public:
   SUBLW(uint16_t literal);
 void execute(); 
};
