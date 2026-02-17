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

    memoryInterface->writeStatusBit(MemoryInterface::StatusBits::C, result > 0xFF);
    memoryInterface->writeStatusBit(MemoryInterface::StatusBits::DC, ((fileValue & 0x0F) + (WValue & 0x0F)) > 0x0F);
    SET_ZERO_FLAG

    return 0;
}

std::string ADDWF::getName()
{
    return "addwf";
}

