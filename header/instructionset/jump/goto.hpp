#pragma once

#include "jump.hpp"

class GOTO  : public Jump 
{
  public:
    GOTO(uint16_t instruction);
    uint16_t execute(); 

    std::string getName();
};
