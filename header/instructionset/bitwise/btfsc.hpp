#pragma once

#include "bitwise.hpp"
#include "jump.hpp"

class BTFSC : public Bitwise, public Jump
{
  public:
    BTFSC(uint16_t instruction);
    uint16_t execute(); 

    std::string getName();
};
