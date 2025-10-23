#pragma once

#include "../instruction.hpp"

class RRF   : public Instruction 
{
    private:
      uint16_t destination;
      uint16_t file;
   public:
   RRF(uint16_t destination, uint16_t file);
 void execute(); 
};
