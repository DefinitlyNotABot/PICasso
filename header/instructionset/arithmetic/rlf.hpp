#pragma once

#include "arithmetic.hpp"

class RLF   : public Arithmetic 
{
  public:
    RLF(uint16_t instruction);
    uint16_t execute(); 
};
