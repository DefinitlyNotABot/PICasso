#include "movwf.hpp"

MOVWF::MOVWF(uint16_t instruction) {
    file = instruction & 0b01111111;
}

uint16_t MOVWF::execute()
{
    loadCurrentValues();
    storeResult(WValue);
    return 0;
}

std::string MOVWF::getName()
{
    return "movwf";
}

