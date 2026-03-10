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
        return 2; // execution time in cycles (1 for incf + 1 for skipping the next instruction)
    }

    return 1; // execution time in cycles
}

std::string INCFSZ::getName()
{
    return "incfsz";
}

