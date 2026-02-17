#pragma once

#include "instruction.hpp"

#define SET_ZERO_FLAG memoryInterface->writeStatusBit(MemoryInterface::StatusBits::Z, (result & 0xFF) == 0);

class Arithmetic : public virtual Instruction 
{
    protected:
        uint16_t destination;
        uint16_t file;
        uint8_t fileValue;
        uint8_t WValue;
        void storeResult(uint16_t result);
        void loadCurrentValues();

         
    public:
        uint16_t getDestination();
        uint16_t getFile();
};
