#include "movwf.hpp"

MOVWF::MOVWF(uint16_t instruction) {
    file = instruction & 0b01111111;
    destination = 1;
}

uint16_t MOVWF::execute()
{
    loadCurrentValues();
    storeResult(WValue);
    return 1; // execution time in cycles
}

std::string MOVWF::getName()
{
    return "movwf";
}

