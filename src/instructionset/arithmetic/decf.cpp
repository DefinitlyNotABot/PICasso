#include "decf.hpp"

DECF::DECF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t DECF::execute()
{
    loadCurrentValues();
    uint16_t result = (fileValue - 1) & 0xFF;
    storeResult(result);
    SET_ZERO_FLAG
    return 0;
}

std::string DECF::getName()
{
    return "decf";
}

