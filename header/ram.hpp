#pragma once
#include "register.hpp"
#include <cstdint>
#include <stdexcept>

class Ram
{
private:
    Register* memory[256]; // Array von Zeigern auf Register

public:
    Ram();
    ~Ram();
    void reset();
    uint8_t readRegister(uint8_t address);
    void writeRegister(uint8_t address, uint8_t value);
    void writeBit(uint8_t address, uint8_t bit, bool value);
    bool readBit(uint8_t address, uint8_t bit);
    void writeHighNibble(uint8_t address, uint8_t value);
    void writeLowNibble(uint8_t address, uint8_t value);
};
