#pragma once

#include <vector>

#include "logger.hpp"
#include "instruction.hpp"
#include "instructionset.hpp"
#include "filereader.hpp"
#include "compiler.hpp"

class Program
{
    private:
        Logger logger;
        Filereader filereader;
        Compiler compiler;

        std::vector<Instruction*> instructionOrder;

    public:
        Program();

        void loadProgram(std::string filename);
};