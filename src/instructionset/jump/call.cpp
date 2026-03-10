#include "call.hpp"

CALL::CALL(uint16_t instruction) {
    address = instruction & 0x7FF;
}

uint16_t CALL::execute()
{
    memoryInterface->pushToStack(memoryInterface->getProgramCounter());
    memoryInterface->setProgramCounter(address);
    return 2; // execution time in cycles (1 for call + 1 for the jump)
}

std::string CALL::getName()
{
    return "call";
}

