#include "alu.hpp"
#include "arithmetic.hpp"
#include "bitwise.hpp"
#include "jump.hpp"
#include "literal.hpp"
#include "ret.hpp"
#include <iostream>
#include <string>

void ALU::executeInstruction(Instruction& instruction)
{
    uint16_t executionReturn = instruction.execute();
    std::string out = "";
    try {
        auto& check = dynamic_cast<Arithmetic&>(instruction);
        out += "Arithmetic ";
    } catch (const std::bad_cast&) {}

    try {
        auto& check = dynamic_cast<Bitwise&>(instruction);
        out += "Bitwise ";
    } catch (const std::bad_cast&) {}

    try {
        auto& check = dynamic_cast<Jump&>(instruction);
        out += "Jump ";
    } catch (const std::bad_cast&) {}

    try {
        auto& check = dynamic_cast<Literal&>(instruction);
        out += "Literal ";
    } catch (const std::bad_cast&) {}

    try {
        auto& check = dynamic_cast<Return&>(instruction);
        out += "Return ";
    } catch (const std::bad_cast&) {}

    if(out == "") out = "NoFit"; 

    std::cout << out << std::endl;
}