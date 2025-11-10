#pragma once

#include "arithmetic.hpp"

class IORWF : public Arithmetic 
{ 
   public:
      IORWF(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
