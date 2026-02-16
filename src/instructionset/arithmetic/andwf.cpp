#include "andwf.hpp"

ANDWF::ANDWF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t ANDWF::execute()
{
    loadCurrentValues();

    uint16_t result = fileValue & WValue;

    storeResult(result);

    SET_ZERO_FLAG

    return 0;
}

std::string ANDWF::getName()
{
    return "andwf";
}

