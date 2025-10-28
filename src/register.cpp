#include "../header/register.hpp"

Register::Register()
: memory(0)
{
}

uint8_t Register::getValue() const
{
    return memory;
}

uint8_t Register::getHighByte() const
{
    return (memory >> 4) & 0x0F;
}

uint8_t Register::getLowByte() const
{
    return memory & 0x0F;
}
        
void Register::setByte(uint8_t byte)
{
    memory = byte;
}

void Register::setHighByte(uint8_t byte)
{
    memory = (memory & 0x0F) | ((byte & 0x0F) << 4);
}

void Register::setLowByte(uint8_t byte)
{
    memory = (memory & 0xF0) | (byte & 0x0F);
}