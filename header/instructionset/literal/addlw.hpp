#pragma once

#include "literal.hpp"

class ADDLW : public Literal 
{
   public:
      ADDLW(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
