#pragma once

#include "bitwise.hpp"
#include "jump.hpp"

class BTFSS : public Bitwise, public Jump
{
  public:
    BTFSS(uint16_t instruction);
    uint16_t execute(); 

    std::string getName();
};
