#pragma once

#include "arithmetic.hpp"

class ANDWF : public Arithmetic 
{
   public:
      ANDWF(uint16_t instruction);
      uint16_t execute(); 
};
