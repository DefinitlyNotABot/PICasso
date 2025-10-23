#pragma once

#include "../instruction.hpp"

class INCF  : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      INCF(uint16_t destination, uint16_t file);
      void execute(); 
};
