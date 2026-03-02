#pragma once

#include "ret.hpp"
#include "jump.hpp"

class RETURN: public Return, public Jump
{
 public:
      RETURN(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
