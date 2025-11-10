#pragma once

#include "../instruction.hpp"

class SLEEP : public Instruction 
{
 public:
    SLEEP(uint16_t instruction);
 uint16_t execute(); 
};
