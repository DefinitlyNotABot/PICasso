#include "../header/ram.hpp"

Ram::Ram()
{
    for (int i = 0; i < 256; i++)
    {
        memory[i] = new Register();

        if (i == 0x07 || (i >= 0x50 && i <= 0x7F) || i == 0x87 || (i >= 0xD0 && i <= 0xFF))
        {
            delete memory[i];
            memory[i] = nullptr;
        }
    }

    reset();
}

Ram::~Ram()
{
    for (int i = 0; i < 256; i++)
    {
        delete memory[i];
    }
}

void Ram::reset()
{
    memory[0x03]->writeBit(3, true);
    memory[0x03]->writeBit(4, true);

    memory[0x81]->writeByte(0xFF);
    memory[0x83]->writeBit(3, true);
    memory[0x83]->writeBit(4, true);
    memory[0x85]->writeByte(0x1F);
    memory[0x86]->writeByte(0xFF);
}

uint8_t Ram::readRegister(uint8_t address)
{
    if (address > 255)
        throw std::runtime_error("Address out of range");

    if (!memory[address])
    {
        throw std::runtime_error("Nullpointer access at address 0x" +
                                 std::to_string(address));
    }

    return memory[address]->readByte();
}

void Ram::writeRegister(uint8_t address, uint8_t value)
{
    if (!memory[address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[address]->writeByte(value);
}
