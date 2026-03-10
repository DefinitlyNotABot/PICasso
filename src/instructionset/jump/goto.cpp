#include "goto.hpp"

GOTO::GOTO(uint16_t instruction) {
    address = instruction & 0x7FF;
}

uint16_t GOTO::execute()
{
    memoryInterface->setProgramCounter(address);
    return 2; // execution time in cycles (1 for goto + 1 for the jump)
}

std::string GOTO::getName()
{
    return "goto";
}

