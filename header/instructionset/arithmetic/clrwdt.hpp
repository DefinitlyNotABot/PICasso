#pragma once

#include "arithmetic.hpp"

class CLRWDT: public Arithmetic 
{
   public:
      CLRWDT(uint16_t instruction);
      uint16_t execute(); 
};
