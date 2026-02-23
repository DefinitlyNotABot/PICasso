#include "ram.hpp"

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

void Ram::writeBit(uint8_t address, uint8_t bit, bool value)
{
    if (!memory[address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[address]->writeBit(bit, value);
}

bool Ram::readBit(uint8_t address, uint8_t bit)
{
    if (!memory[address])
    {
        throw std::runtime_error("Nullpointer access at address 0x" +
                                 std::to_string(address));
    }

    return memory[address]->readBit(bit);
}

void Ram::writeHighNibble(uint8_t address, uint8_t value)
{
    if (!memory[address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[address]->writeHighNibble(value);
}

void Ram::writeLowNibble(uint8_t address, uint8_t value)
{
    if (!memory[address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[address]->writeLowNibble(value);
}

int *Ram::readRAM()
{
    // 20 x 8 = 160 Register, die tatsächlich existieren
    int *ramValues = new int[160];

    // 10 x 8 = 80 Register bis erste nicht existierende Adresse
    for (int i = 0; i < 80; i++)
    {
        ramValues[i] = memory[i]->readByte();
    }

    // register 0x80 bis 0xCF
    for (int i = 0; i < 80; i++)
    {
        ramValues[0x80 + i] = memory[0x80 + i]->readByte();
    }

    return ramValues;
}
