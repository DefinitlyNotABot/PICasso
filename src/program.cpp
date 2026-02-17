#include "program.hpp"


Program::Program(): logger("Program")
{

};


void Program::loadProgram(std::string filename)
{
    auto [validFileRead, fileContent] = filereader.readFile(filename);

    if(!validFileRead)
    {
        logger.log(std::string("Received invalid file"), Logger::LogLevel::ERROR);
        return;
    }

    std::vector<std::unique_ptr<Instruction>> compiled = compiler.compileSourcecode(fileContent);

    if(compiled.empty()){
        logger.log(std::string("Compilation failed"), Logger::LogLevel::ERROR);
        return;
    }

    instructionOrder.clear();
    instructionOrder = std::move(compiled);

    logger.log(std::string(("Successfully loaded file")), Logger::LogLevel::INFO);
}




uint16_t Program::getProgramLength(){
    return instructionOrder.size();
}


Instruction& Program::getInstructionAt(uint16_t index) {
    return *instructionOrder.at(index); // throws std::out_of_range if index invalid
}
