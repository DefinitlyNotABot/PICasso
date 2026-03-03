#pragma once

#include "ret.hpp"
#include "jump.hpp"

class RETFIE: public Return, public Jump
{
 public:
      RETFIE(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
