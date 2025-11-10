#pragma once

#include "arithmetic.hpp"

class INCFSZ  : public Arithmetic 
{
   public:
      INCFSZ(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
