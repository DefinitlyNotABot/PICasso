#include "memoryInterface.hpp"

MemoryInterface::MemoryInterface(): ram()
{
}

uint8_t MemoryInterface::readRegister(uint8_t address)
{
    return ram.readRegister(address);
}

void MemoryInterface::writeRegister(uint8_t address, uint8_t value)
{
    ram.writeRegister(address, value);
}

void MemoryInterface::writeBit(uint8_t address, uint8_t bit, bool value)
{
    ram.writeBit(address, bit, value);
}

bool MemoryInterface::readBit(uint8_t address, uint8_t bit)
{
    return ram.readBit(address, bit);
}

void MemoryInterface::writeHighNibble(uint8_t address, uint8_t value)
{
    ram.writeHighNibble(address, value);
}

void MemoryInterface::writeLowNibble(uint8_t address, uint8_t value)
{
    ram.writeLowNibble(address, value);
}

void MemoryInterface::writeStatusBit(StatusBits bit, bool value)
{
    ram.writeBit(RegisterAddresses::STATUS, static_cast<uint8_t>(bit), value);
}

bool MemoryInterface::readStatusBit(StatusBits bit)
{
    return ram.readBit(RegisterAddresses::STATUS, static_cast<uint8_t>(bit));
}
