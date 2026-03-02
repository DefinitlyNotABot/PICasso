#include "prescaler.hpp"

Prescaler::Prescaler() : prescaleCounter(0) {}

Prescaler::~Prescaler() {}

Prescaler::Prescaler(std::shared_ptr<MemoryInterface> memoryInterface) : prescaleCounter(0), memoryInterface(memoryInterface) {}

int Prescaler::step(Source source){
    uint8_t optionReg = memoryInterface->readRegister(MemoryInterface::OPTION_REG, 1);
    bool psa = (optionReg >> 3) & 0x01; // Prescaler Assignment bit
    uint8_t prescalerRate = optionReg & 0x07; // Prescaler Rate Select bits

    if ((psa && source == TMR0)) {
        prescaleCounter++;
        int threshold = 1 << (prescalerRate + 1); // Calculate the threshold based on the rate
        if (prescaleCounter >= threshold) {
            prescaleCounter = 0; // Reset the counter
            return 1; // Indicate that a tick should occur
        }
    }else if(source == TMR0){
        return 1; // If prescaler is assigned to WDT, TMR0 ticks every cycle
    }
    return 0;
}

