#include "../header/program.hpp"


Program::Program(): logger("Program")
{

};


void Program::loadProgram(std::string filename)
{
    auto [validFileRead, fileContent] = filereader.readFile(filename);

    if(!validFileRead)
    {
        logger.log("Received invalid file");
        return;
    }

    auto [validCompile, compiled] = compiler.compileSourcecode(fileContent);

    if(!validCompile){
        logger.log("Compilation failed");
        return;
    }

    instructionOrder.clear();
    instructionOrder = compiled;

    logger.log("Successfully loaded file");
}