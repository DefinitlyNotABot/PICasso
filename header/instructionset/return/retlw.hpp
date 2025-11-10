#pragma once

#include "ret.hpp"
#include "literal.hpp"

class RETLW : public Literal, public Return
{
  public:
    RETLW(uint16_t instruction);
    uint16_t execute(); 
};
