#pragma once

#include "ram.hpp"
#include "stack.hpp"

class MemoryInterface
{
    private:
        Ram ram;
        Stack stack;


    public:
        MemoryInterface();
        ~MemoryInterface() = default;

        enum StatusBits {
            C = 0,      // Carry Flag
            DC = 1,     // Digital Carry Flag
            Z = 2,      // Zero Flag
            PD = 3,     // Power-Down Flag
            TO = 4,     // Time-Out Flag
            RP0 = 5,    // Register Bank Select bit 0
            RP1 = 6,    // Register Bank Select bit 1
            IRP = 7     // Indirect Register Bank Select bit
        };

        enum RegisterAddresses {
            INDF = 0x00, // Indirect Register
            TMR0 = 0x01, // Timer0 Register
            PCL = 0x02,  // Program Counter Low Byte
            STATUS = 0x03, // Status Register
            FSR = 0x04,  // File Select Register
            PORTA = 0x05, // Port A Register
            PORTB = 0x06, // Port B Register
            PCLATH = 0x0A, // Program Counter Latch High Byte
            INTCON = 0x0B // Interrupt Control Register
        };

        uint8_t readRegister(uint8_t address);
        void writeRegister(uint8_t address, uint8_t value);
        void writeBit(uint8_t address, uint8_t bit, bool value);
        bool readBit(uint8_t address, uint8_t bit);
        void writeHighNibble(uint8_t address, uint8_t value);
        void writeLowNibble(uint8_t address, uint8_t value);
        void writeStatusBit(StatusBits bit, bool value);
        bool readStatusBit(StatusBits bit);

        void reset();

        uint8_t getProgramCounter();
        void setProgramCounter(uint8_t value);
        void incrementProgramCounterLow();

        void pushToStack(uint8_t value);
        uint8_t popFromStack();
        
        int* readRAM();
};