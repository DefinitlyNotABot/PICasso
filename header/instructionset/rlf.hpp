#pragma once

#include "../instruction.hpp"

class RLF   : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   RLF(uint16_t destination, uint16_t file);
 void execute(); 
};
