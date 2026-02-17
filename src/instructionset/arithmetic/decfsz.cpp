#include "decfsz.hpp"

DECFSZ::DECFSZ(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t DECFSZ::execute()
{
    loadCurrentValues();
    uint16_t result = (fileValue - 1) & 0xFF;
    storeResult(result);

    if(result == 0){
        memoryInterface->incrementProgramCounterLow();
    }

    return 0;
}

std::string DECFSZ::getName()
{
    return "decfsz";
}

