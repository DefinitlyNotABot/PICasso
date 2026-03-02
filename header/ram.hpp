#pragma once
#include "register.hpp"
#include <cstdint>
#include <stdexcept>

class Ram
{
private:
    Register *memory[2][0x50]; // Array von Zeigern auf Register

    static const uint8_t STATUS_REGISTER_ADDRESS = 0x03; // Adresse des Statusregisters

    bool readBankSelectBit() const;
    bool isOutOfScope(uint8_t address) const;

public:
    Ram();
    ~Ram();
    Ram(const Ram &) = delete;
    Ram &operator=(const Ram &) = delete;
    void reset();
    uint8_t readRegister(uint8_t address);
    uint8_t readRegister(uint8_t address, bool bank);
    void writeRegister(uint8_t address, uint8_t value);
    void writeRegister(uint8_t address, uint8_t value, bool bank);
    void writeBit(uint8_t address, uint8_t bit, bool value);
    bool readBit(uint8_t address, uint8_t bit);
    void writeHighNibble(uint8_t address, uint8_t value);
    void writeLowNibble(uint8_t address, uint8_t value);
};
