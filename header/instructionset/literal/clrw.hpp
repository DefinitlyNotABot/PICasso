#pragma once

#include "literal.hpp"

class CLRW  : public Literal 
{
 public:
    CLRW(uint16_t instruction);
    uint16_t execute(); 
};
