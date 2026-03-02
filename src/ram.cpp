#include "ram.hpp"

bool Ram::readBankSelectBit() const
{
    return memory[0][STATUS_REGISTER_ADDRESS]->readBit(5);
}

bool Ram::isOutOfScope(uint8_t address) const
{
    return address > 0x4F;
}

Ram::Ram()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 0x50; j++)
        {
            if (i == 1 && (j == 0x02 || j == 0x03 || j == 0x04 || j == 0x0A || j == 0x0B))
            {
                memory[i][j] = memory[0][j];
                continue;
            }
            if (j == 0x07)
            {
                memory[i][j] = nullptr;
                continue;
            }
            memory[i][j] = new Register();
        }
    }
    reset();
}

Ram::~Ram()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 0x50; j++)
        {
            if (i == 1 && (j == 0x02 || j == 0x03 || j == 0x04 || j == 0x0A || j == 0x0B))
            {
                continue;
            }
            delete memory[i][j];
        }
    }
}

void Ram::reset()
{
    memory[0][0x03]->writeBit(3, true);
    memory[0][0x03]->writeBit(4, true);

    memory[1][0x01]->writeByte(0xFF);
    memory[1][0x03]->writeBit(3, true);
    memory[1][0x03]->writeBit(4, true);
    memory[1][0x05]->writeByte(0x1F);
    memory[1][0x06]->writeByte(0xFF);
}

uint8_t Ram::readRegister(uint8_t address)
{
    if (isOutOfScope(address))
        throw std::runtime_error("Address out of range");

    if (!memory[readBankSelectBit()][address])
    {
        throw std::runtime_error("Nullpointer access at address 0x" +
                                 std::to_string(address));
    }

    return memory[readBankSelectBit()][address]->readByte();
}

uint8_t Ram::readRegister(uint8_t address, bool bank)
{
    if (isOutOfScope(address))
        throw std::runtime_error("Address out of range");

    if (!memory[bank][address])
    {
        throw std::runtime_error("Nullpointer access at address 0x" +
                                 std::to_string(address));
    }

    return memory[bank][address]->readByte();
}

void Ram::writeRegister(uint8_t address, uint8_t value)
{
    if (isOutOfScope(address))
        throw std::runtime_error("Address out of range");

    if (!memory[readBankSelectBit()][address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[readBankSelectBit()][address]->writeByte(value);
}

void Ram::writeRegister(uint8_t address, uint8_t value, bool bank)
{
    if (isOutOfScope(address))
        throw std::runtime_error("Address out of range");

    if (!memory[bank][address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[bank][address]->writeByte(value);
}

void Ram::writeBit(uint8_t address, uint8_t bit, bool value)
{
    if (isOutOfScope(address))
        throw std::runtime_error("Address out of range");

    if (!memory[readBankSelectBit()][address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[readBankSelectBit()][address]->writeBit(bit, value);
}

bool Ram::readBit(uint8_t address, uint8_t bit)
{
    if (isOutOfScope(address))
        throw std::runtime_error("Address out of range");

    if (!memory[readBankSelectBit()][address])
    {
        throw std::runtime_error("Nullpointer access at address 0x" +
                                 std::to_string(address));
    }

    return memory[readBankSelectBit()][address]->readBit(bit);
}

void Ram::writeHighNibble(uint8_t address, uint8_t value)
{
    if (isOutOfScope(address))
        throw std::runtime_error("Address out of range");

    if (!memory[readBankSelectBit()][address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[readBankSelectBit()][address]->writeHighNibble(value);
}

void Ram::writeLowNibble(uint8_t address, uint8_t value)
{
    if (isOutOfScope(address))
        throw std::runtime_error("Address out of range");

    if (!memory[readBankSelectBit()][address])
    {
        throw std::runtime_error("Nullpointer write at address 0x" +
                                 std::to_string(address));
    }

    memory[readBankSelectBit()][address]->writeLowNibble(value);
}
