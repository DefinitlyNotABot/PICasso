#pragma once

#include "arithmetic.hpp"

class INCF  : public Arithmetic 
{
   public:
      INCF(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
