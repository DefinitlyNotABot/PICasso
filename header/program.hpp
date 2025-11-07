#pragma once

#include <memory>

#include "logger.hpp"
#include "instruction.hpp"
#include "filereader.hpp"
#include "compiler.hpp"

class Program
{
    private:
        Logger logger;
        Filereader filereader;
        Compiler compiler;

        std::vector<std::unique_ptr<Instruction>> instructionOrder;

    public:
        Program();

        void loadProgram(std::string filename);
};