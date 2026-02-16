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

    // TODO: jump when 0

    return 0;
}

std::string DECFSZ::getName()
{
    return "decfsz";
}

