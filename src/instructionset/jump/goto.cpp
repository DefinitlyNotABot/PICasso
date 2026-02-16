#include "goto.hpp"

GOTO::GOTO(uint16_t instruction) {
    address = instruction & 0x7FF;
}

uint16_t GOTO::execute()
{
    return 0;
}

std::string GOTO::getName()
{
    return "goto";
}

