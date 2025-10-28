#pragma once

#include <memory>
#include <string>
#include <vector>

#include "instruction.hpp"
#include "logger.hpp"

class Compiler
{
    private:
        Logger logger;

        std::unique_ptr<Instruction>  getInstruction(const uint16_t instruction);
    public:
        Compiler();
        std::vector<std::unique_ptr<Instruction>> compileSourcecode(std::string& code);
};