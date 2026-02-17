#include "call.hpp"

CALL::CALL(uint16_t instruction) {
    address = instruction & 0x7FF;
}

uint16_t CALL::execute()
{
    memoryInterface->pushToStack(memoryInterface->getProgramCounter());
    memoryInterface->setProgramCounter(address);
    return 0;
}

std::string CALL::getName()
{
    return "call";
}

