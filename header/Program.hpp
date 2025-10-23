#pragma once

#include <vector>

#include "instruction.hpp"

class Program
{
    private:
        std::vector<Instruction> instructionOrder;

    public:
        Program();
}