#include "clrf.hpp"

CLRF::CLRF(uint16_t instruction) {
    file = instruction & 0b01111111;
}

uint16_t CLRF::execute()
{
    memoryInterface->writeRegister(file, 0);
    memoryInterface->writeStatusBit(MemoryInterface::StatusBits::Z, true);
    return 0;
}

std::string CLRF::getName()
{
    return "clrf";
}

