#include "memoryInterface.hpp"

MemoryInterface::MemoryInterface(): ram(), stack()
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

void MemoryInterface::reset()
{
    ram.reset();
    stack.reset();
}

uint8_t MemoryInterface::getProgramCounter()
{
    return ram.readRegister(RegisterAddresses::PCL);
}

void MemoryInterface::setProgramCounter(uint8_t value)
{
    ram.writeRegister(RegisterAddresses::PCL, value);
}

void MemoryInterface::incrementProgramCounterLow()
{
    uint8_t pcl = getProgramCounter();
    setProgramCounter(pcl + 1);
}

void MemoryInterface::pushToStack(uint8_t value)
{
    stack.push(value);
}

uint8_t MemoryInterface::popFromStack()
{
    return stack.pop();
}
