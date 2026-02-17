#include "compiler.hpp"
#include "instructionList.hpp"


#include <vector>
#include <sstream>
#include <string>
#include <iostream>


Compiler::Compiler(): logger("Compiler")
{

}

std::vector<std::unique_ptr<Instruction>> Compiler::compileSourcecode(std::string& code)
{

    std::vector<std::unique_ptr<Instruction>> compilationOutput = {};

    std::istringstream stream(code);
    std::string line;

    while (std::getline(stream, line))
    {
        if (!line.empty() && line[0] == ' ')
            continue;

        std::string combined = line.substr(5, 4);
        uint16_t number = static_cast<uint16_t>(std::stoi(combined, nullptr, 16));

        std::unique_ptr<Instruction> instruction = getInstruction(number);

        if(instruction == nullptr){
            logger.log("ERROR: Invalid instruction at " + line, Logger::LogLevel::ERROR);
            compilationOutput.clear();
            return {};
        }

        compilationOutput.push_back(std::move(instruction));
        logger.log(line, Logger::LogLevel::INFO);
    }



    return compilationOutput;
}


std::unique_ptr<Instruction> Compiler::getInstruction(const uint16_t instruction)
{
    
    uint16_t bitmap7bit = 0b0011111110000000;
    uint16_t bitmap6bit = 0b0011111100000000;
    uint16_t bitmap5bit = 0b0011111000000000;
    uint16_t bitmap4bit = 0b0011110000000000;
    uint16_t bitmap3bit = 0b0011100000000000;

    uint16_t instructionMapped;

    switch(instruction)
    {
        case 0x0064: // CLRWDT            
            return std::make_unique<CLRWDT>(instruction);
        case 0x0009: // RETFIE
            return std::make_unique<RETFIE>(instruction);
        case 0x0008: // RETURN
            return std::make_unique<RETURN>(instruction);
        case 0x0063: // SLEEP
            return std::make_unique<SLEEP>(instruction);
        default:
            break;
    }

    instructionMapped = instruction & bitmap7bit;

    switch (instructionMapped)
    {
    case 0x0180: // CLRF
        return std::make_unique<CLRF>(instruction);
    case 0x0100: // CLRW
        return std::make_unique<CLRW>(instruction);
    case 0x0080: // MOVWF
        return std::make_unique<MOVWF>(instruction);
    case 0x0000: // NOP
        return std::make_unique<NOP>(instruction);
    default:
        break;
    }


    instructionMapped = instruction & bitmap6bit;
    switch (instructionMapped)
    {
    case 0x0700: // ADDWF
        return std::make_unique<ADDWF>(instruction);
    case 0x0500: // ANDWF        
        return std::make_unique<ANDWF>(instruction);
    case 0x0900: // COMF        
        return std::make_unique<COMF>(instruction);
    case 0x0300: // DECF
        return std::make_unique<DECF>(instruction);
    case 0x0B00: // DECFSZ
        return std::make_unique<DECFSZ>(instruction);
    case 0x0A00: // INCF
        return std::make_unique<INCF>(instruction);
    case 0x0F00: // INCFSZ
        return std::make_unique<INCFSZ>(instruction);
    case 0x0400: // IORWF
        return std::make_unique<IORWF>(instruction);
    case 0x0800: // MOVF
        return std::make_unique<MOVF>(instruction);
    case 0x0D00: // RLF
        return std::make_unique<RLF>(instruction);
    case 0x0C00: // RRF
        return std::make_unique<RRF>(instruction);
    case 0x0200: // SUBWF
        return std::make_unique<SUBWF>(instruction);
    case 0x0E00: // SWAPF
        return std::make_unique<SWAPF>(instruction);
    case 0x0600: // XORWF
        return std::make_unique<XORWF>(instruction);
    case 0x3900: // ANDLW        
        return std::make_unique<ANDLW>(instruction);
    case 0x3800: // IORLW
        return std::make_unique<IORLW>(instruction);
    case 0x3A00: // XORLW
        return std::make_unique<XORLW>(instruction);
    default:
        break;
    }
    instructionMapped = instruction & bitmap5bit;
    switch (instructionMapped)
    {
        case 0x3E00: // ADDLW
            return std::make_unique<ADDLW>(instruction);
        case 0x3C00: // SUBLW
            return std::make_unique<SUBLW>(instruction);
        default:
            break;
    }
    instructionMapped = instruction & bitmap4bit;
    switch (instructionMapped)
    {
        case 0x1000: // BCF            
            return std::make_unique<BCF>(instruction);
        case 0x1400: // BSF
            return std::make_unique<BSF>(instruction);
        case 0x1800: // BTFSC
            return std::make_unique<BTFSC>(instruction);
        case 0x1C00: // BTFSS
            return std::make_unique<BTFSS>(instruction);
        case 0x3000: // MOVLW
            return std::make_unique<MOVLW>(instruction);
        case 0x3400: // RETLW
            return std::make_unique<RETLW>(instruction);
        default:
            break;
    }
    instructionMapped = instruction & bitmap3bit;

    switch (instructionMapped)
    {
        case 0x2000: // CALL
            return std::make_unique<CALL>(instruction);
        case 0x2800: // GOTO
            return std::make_unique<GOTO>(instruction);
        default:
            break;
    }

    return nullptr;
}
