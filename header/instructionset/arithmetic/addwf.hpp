#pragma once

#include "arithmetic.hpp"

class ADDWF : public Arithmetic 
{
   public:
      ADDWF(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
