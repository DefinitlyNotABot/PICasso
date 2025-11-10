#pragma once

#include "literal.hpp"

class ANDLW : public Literal 
{
   public:
      ANDLW(uint16_t instruction);
      uint16_t execute(); 
};
