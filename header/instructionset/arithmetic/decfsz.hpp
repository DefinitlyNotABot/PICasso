#pragma once

#include "arithmetic.hpp"

class DECFSZ: public Arithmetic 
{
   public:
      DECFSZ(uint16_t instruction);
 uint16_t execute(); 

    std::string getName();
};
