#pragma once

#include "../instruction.hpp"

class ADDWF : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      ADDWF(uint16_t destination, uint16_t file);
 void execute(); 
};
