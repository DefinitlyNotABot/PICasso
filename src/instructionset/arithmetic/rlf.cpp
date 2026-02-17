#include "rlf.hpp"

RLF::RLF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t RLF::execute()
{
    loadCurrentValues();

    uint8_t carry = memoryInterface->readStatusBit(MemoryInterface::StatusBits::C) ? 1 : 0;
    uint16_t result = ((fileValue << 1) | carry);

    storeResult(result);

    memoryInterface->writeStatusBit(MemoryInterface::StatusBits::C, (fileValue & 0x80) != 0);
    SET_ZERO_FLAG

    return 0;
}

std::string RLF::getName()
{
    return "rlf";
}

