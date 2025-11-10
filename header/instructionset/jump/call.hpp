#pragma once

#include "jump.hpp"

class CALL  : public Jump 
{
  public:
    CALL(uint16_t instruction);
    uint16_t execute(); 
};
