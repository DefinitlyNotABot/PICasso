#pragma once
#include "memory/register.hpp"
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
};
