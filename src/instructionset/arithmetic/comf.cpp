#include "comf.hpp"

COMF::COMF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t COMF::execute()
{
    loadCurrentValues();
    uint16_t result = ~fileValue;
    storeResult(result);
    SET_ZERO_FLAG
    return 0;
}

std::string COMF::getName()
{
    return "comf";
}

