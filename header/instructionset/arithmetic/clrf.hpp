#pragma once

#include "arithmetic.hpp"

class CLRF  : public Arithmetic 
{
      public:
      CLRF(uint16_t instruction);
      uint16_t execute();

    std::string getName();
};
