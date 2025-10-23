#pragma once

#include "../instruction.hpp"

class INCFSZ  : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      INCFSZ(uint16_t destination, uint16_t file);
      void execute(); 
};
