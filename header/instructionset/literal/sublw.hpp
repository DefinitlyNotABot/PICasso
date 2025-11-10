#pragma once

#include "literal.hpp"

class SUBLW : public Literal 
{
   public:
      SUBLW(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
