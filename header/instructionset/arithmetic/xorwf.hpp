#pragma once

#include "arithmetic.hpp"

class XORWF : public Arithmetic 
{
  public:
    XORWF(uint16_t instruction);
    uint16_t execute(); 
};
