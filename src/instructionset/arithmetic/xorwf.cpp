#include "xorwf.hpp"

XORWF::XORWF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t XORWF::execute()
{
    loadCurrentValues();
    uint16_t result = fileValue ^ WValue;
    storeResult(result);
    SET_ZERO_FLAG
    return 0;
}

std::string XORWF::getName()
{
    return "xorwf";
}

