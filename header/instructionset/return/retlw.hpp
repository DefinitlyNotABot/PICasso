#pragma once

#include "ret.hpp"
#include "literal.hpp"
#include "jump.hpp"

class RETLW : public Literal, public Return, public Jump
{
  public:
    RETLW(uint16_t instruction);
    uint16_t execute(); 

    std::string getName();
};
