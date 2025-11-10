#pragma once

#include "arithmetic.hpp"

class COMF  : public Arithmetic 
{
   public:
      COMF(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
