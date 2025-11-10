#pragma once

#include "arithmetic.hpp"

class SWAPF : public Arithmetic 
{
  public:
    SWAPF(uint16_t instruction);
    uint16_t execute(); 
};
