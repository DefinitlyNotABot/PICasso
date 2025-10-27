#pragma once

#include "../instruction.hpp"

class CLRF  : public Instruction 
{
    uint16_t file;
 public:
    CLRF(uint16_t instruction);
 void execute();
};
