#pragma once

#include "literal.hpp"

class MOVLW : public Literal 
{
  public:
    MOVLW(uint16_t instruction);
    uint16_t execute(); 
};
