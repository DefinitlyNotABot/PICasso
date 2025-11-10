#pragma once

#include "bitwise.hpp"

class BTFSC : public Bitwise 
{
  public:
    BTFSC(uint16_t instruction);
    uint16_t execute(); 
};
