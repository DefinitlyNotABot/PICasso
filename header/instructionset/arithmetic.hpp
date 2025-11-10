#pragma once

#include "instruction.hpp"

class Arithmetic : public virtual Instruction 
{
    protected:
        uint16_t destination;
        uint16_t file;
    public:
        uint16_t getDestination();
        uint16_t getFile();
};
