#pragma once

#include <vector>

#include "logger.hpp"
#include "instruction.hpp"

class Program
{
    private:
        Logger logger;
        std::vector<Instruction> instructionOrder;

    public:
        Program();
};