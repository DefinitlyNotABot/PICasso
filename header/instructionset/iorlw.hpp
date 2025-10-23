#pragma once

#include "../instruction.hpp"

class IORLW : public Instruction 
{
    private:
      uint16_t literal;
   public:
   IORLW(uint16_t literal);
 void execute(); 
};
