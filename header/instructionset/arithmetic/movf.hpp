#pragma once

#include "arithmetic.hpp"

class MOVF  : public Arithmetic 
{
  public:
    MOVF(uint16_t instruction);
    uint16_t execute(); 

};
