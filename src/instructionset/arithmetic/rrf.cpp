#include "rrf.hpp"

RRF::RRF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t RRF::execute()
{
    loadCurrentValues();

    uint8_t carry = ram->readStatusBit(Ram::C) ? 1 : 0;
    uint16_t result = (fileValue >> 1) | (carry << 7);

    storeResult(result);

    ram->writeStatusBit(Ram::C, (fileValue & 0x01) != 0);
    SET_ZERO_FLAG

    return 0;
}

std::string RRF::getName()
{
    return "rrf";
}

