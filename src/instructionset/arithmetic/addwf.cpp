#include "addwf.hpp"

ADDWF::ADDWF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t ADDWF::execute()
{
    loadCurrentValues();

    uint16_t result = fileValue + WValue;

    storeResult(result);

    ram->writeStatusBit(Ram::C, result > 0xFF);
    ram->writeStatusBit(Ram::DC, ((fileValue & 0x0F) + (WValue & 0x0F)) > 0x0F);
    SET_ZERO_FLAG

    return 0;
}

std::string ADDWF::getName()
{
    return "addwf";
}

