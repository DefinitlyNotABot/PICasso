#pragma once

#include "bitwise.hpp"

class BCF   : public Bitwise 
{
  public:
    BCF(uint16_t instruction);
    uint16_t execute(); 
};
