#pragma once

#include "ret.hpp"

class RETURN: public Return 
{
 public:
      RETURN(uint16_t instruction);
      uint16_t execute(); 

    std::string getName();
};
