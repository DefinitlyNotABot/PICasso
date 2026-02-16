#pragma once
#include "register.hpp"
#include <cstdint>
#include <stdexcept>

class Ram
{
private:
    Register* memory[256]; // Array von Zeigern auf Register

    static const uint8_t STATUS_REGISTER_ADDRESS = 0x03; // Adresse des Statusregisters

public:
    enum STATUS{
        C = 0,      // Carry Flag
        DC = 1,     // Digital Carry Flag
        Z = 2,      // Zero Flag
        PD = 3,     // Power-Down Flag
        TO = 4,     // Time-Out Flag
        RP0 = 5,    // Register Bank Select bit 0
        RP1 = 6,    // Register Bank Select bit 1
        IRP = 7     // Indirect Register Bank Select bit
    };


    Ram();
    ~Ram();
    void reset();
    uint8_t readRegister(uint8_t address);
    void writeRegister(uint8_t address, uint8_t value);
    void writeBit(uint8_t address, uint8_t bit, bool value);
    bool readBit(uint8_t address, uint8_t bit);
    void writeHighNibble(uint8_t address, uint8_t value);
    void writeLowNibble(uint8_t address, uint8_t value);
    
    void writeStatusBit(STATUS bit, bool value);
    bool readStatusBit(STATUS bit);
};
