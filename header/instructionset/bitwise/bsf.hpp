#pragma once

#include "bitwise.hpp"

class BSF   : public Bitwise 
{
  public:
    BSF(uint16_t instruction);
    uint16_t execute(); 

    std::string getName();
};
