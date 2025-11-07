#pragma once

#include "../instruction.hpp"

class MOVF  : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   MOVF(uint16_t instruction);
 void execute(); 

};
