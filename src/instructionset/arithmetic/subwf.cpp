#include "subwf.hpp"

SUBWF::SUBWF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t SUBWF::execute()
{
    loadCurrentValues();
    uint16_t result = (fileValue - WValue) & 0xFF;
    storeResult(result);
    ram->writeStatusBit(Ram::C, fileValue >= WValue);
    ram->writeStatusBit(Ram::DC, (fileValue & 0x0F) >= (WValue & 0x0F));
    SET_ZERO_FLAG

    return 0;
}

std::string SUBWF::getName()
{
    return "subwf";
}

