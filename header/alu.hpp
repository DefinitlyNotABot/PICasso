#pragma once

#include "instruction.hpp"
#include <memory>

class ALU{
    private:
        
    public:
        uint16_t executeInstruction(Instruction &instruction);        
};