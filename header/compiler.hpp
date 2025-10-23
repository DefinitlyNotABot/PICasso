#pragma once

#include <string>
#include <tuple>
#include <vector>

#include "instruction.hpp"
#include "logger.hpp"

class Compiler
{
    private:
        Logger logger;

        Instruction* getInstruction(const uint16_t instruction);
    public:
        Compiler();
        std::tuple<bool, std::vector<Instruction*>> compileSourcecode(std::string code);
};