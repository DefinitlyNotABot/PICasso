#include "incf.hpp"

INCF::INCF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t INCF::execute()
{
    loadCurrentValues();
    uint16_t result = (fileValue + 1) & 0xFF;
    storeResult(result);
    SET_ZERO_FLAG
    return 0;
}

std::string INCF::getName()
{
    return "incf";
}

