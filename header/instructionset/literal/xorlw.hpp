#pragma once

#include "literal.hpp"

class XORLW : public Literal 
{
  public:
    XORLW(uint16_t instruction);
    uint16_t execute(); 
};
