#pragma once

#include "arithmetic.hpp"

class RRF   : public Arithmetic 
{
  public:
    RRF(uint16_t instruction);
    uint16_t execute(); 
};
