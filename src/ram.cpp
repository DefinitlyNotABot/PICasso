#include "ram.hpp"
#include <stdexcept> 

void Ram::reset()
{
    memory[0x03].writeBit(3, true);
    memory[0x03].writeBit(4, true);

    memory[0x81].writeByte(0xFF);
    memory[0x83].writeBit(3, true);
    memory[0x83].writeBit(4, true);
    memory[0x85].writeByte(0x1F);
    memory[0x86].writeByte(0xFF);
}

Ram::Ram()
{
    reset();
}

uint8_t Ram::readRegister(uint8_t address)
{
    if (address >= 255) throw std::runtime_error("Address out of range");
    
    return memory[address].readByte();
}

void Ram::writeRegister(uint8_t address, uint8_t value)
{
    memory[address].writeByte(value);
}