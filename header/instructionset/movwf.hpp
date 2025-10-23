#pragma once

#include "../instruction.hpp"

class MOVWF : public Instruction 
{
    uint16_t file;
 public:
    MOVWF(uint16_t file);
 void execute(); 
};
