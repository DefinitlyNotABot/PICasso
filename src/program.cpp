#include "program.hpp"


Program::Program(): logger("Program")
{

};


void Program::loadProgram(std::string filename)
{
    auto [validFileRead, fileContent] = filereader.readFile(filename);

    if(!validFileRead)
    {
        logger.log(std::string("Received invalid file"));
        return;
    }

    std::vector<std::unique_ptr<Instruction>> compiled = compiler.compileSourcecode(fileContent);

    if(compiled.empty()){
        logger.log(std::string(("Compilation failed")));
        return;
    }

    instructionOrder.clear();
    instructionOrder = std::move(compiled);

    logger.log(std::string(("Successfully loaded file")));
}