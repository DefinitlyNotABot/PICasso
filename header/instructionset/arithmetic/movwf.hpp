#pragma once

#include "arithmetic.hpp"

class MOVWF : public Arithmetic 
{
   public:
      MOVWF(uint16_t instruction);
      uint16_t execute(); 
};
