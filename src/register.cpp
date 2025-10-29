#include "../header/register.hpp"
#include <stdexcept> 

Register::Register()
: memory(0)
{
}

uint8_t Register::readByte() const
{
    return memory;
}

uint8_t Register::readHighNibble() const
{
    return (memory >> 4) & 0x0F;
}

uint8_t Register::readLowNibble() const
{
    return memory & 0x0F;
}

bool Register::readBit(uint8_t bit) const
{
    if (bit > 7) throw std::runtime_error("Bit index out of range");
    
    return (memory >> bit) & 0x01;
}
        
void Register::writeByte(uint8_t byte)
{
    memory = byte;
}

void Register::writeHighNibble(uint8_t byte)
{
    memory = (memory & 0x0F) | ((byte & 0x0F) << 4);
}

void Register::writeLowNibble(uint8_t byte)
{
    memory = (memory & 0xF0) | (byte & 0x0F);
}

void Register::writeBit(uint8_t bit, bool value)
{
    if (bit > 7) {
        throw std::runtime_error("Bit index out of range");
    } else
    {
        if (value) {
            memory |= (1 << bit);
        } else {
            memory &= ~(1 << bit);
        }
    }
}