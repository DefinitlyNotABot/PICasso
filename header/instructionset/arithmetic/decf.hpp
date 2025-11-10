#pragma once

#include "arithmetic.hpp"

class DECF  : public Arithmetic 
{
   public:
      DECF(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
