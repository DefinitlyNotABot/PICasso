#pragma once

#include "arithmetic.hpp"

class SUBWF : public Arithmetic 
{
  public:
    SUBWF(uint16_t instruction);
    uint16_t execute(); 
};
