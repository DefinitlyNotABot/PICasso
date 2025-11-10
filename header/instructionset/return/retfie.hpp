#pragma once

#include "ret.hpp"

class RETFIE: public Return 
{
 public:
      RETFIE(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
