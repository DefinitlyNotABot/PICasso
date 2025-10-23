#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "instruction.hpp"

class Compiler
{
    public:
        std::tuple<bool, std::vector<Instruction*>> compileSourcecode(std::string code);
};