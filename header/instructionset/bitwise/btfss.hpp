#pragma once

#include "bitwise.hpp"

class BTFSS : public Bitwise 
{
  public:
    BTFSS(uint16_t instruction);
    uint16_t execute(); 
};
