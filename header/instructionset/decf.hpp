#pragma once

#include "../instruction.hpp"

class DECF  : public Instruction 
{
   private:
      uint16_t destination;
      uint16_t file;
   public:
      DECF(uint16_t destination, uint16_t file);
      void execute(); 
};
