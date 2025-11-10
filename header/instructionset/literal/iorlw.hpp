#pragma once

#include "literal.hpp"

class IORLW : public Literal 
{
  public:
    IORLW(uint16_t instruction);
    uint16_t execute(); 
};
