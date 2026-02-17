#include "incfsz.hpp"

INCFSZ::INCFSZ(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t INCFSZ::execute()
{
    loadCurrentValues();
    uint16_t result = (fileValue + 1) & 0xFF;
    storeResult(result);
    SET_ZERO_FLAG

    if(result == 0){
        memoryInterface->incrementProgramCounterLow();
    }

    return 0;
}

std::string INCFSZ::getName()
{
    return "incfsz";
}

