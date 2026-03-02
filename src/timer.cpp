#include "timer.hpp"

Timer::Timer(std::shared_ptr<Prescaler> prescaler, std::shared_ptr<MemoryInterface> memoryInterface) : prescaler(prescaler), memoryInterface(memoryInterface) {}

Timer::~Timer() {}

void Timer::timeStep() {
    uint8_t tmrVal = memoryInterface->readRegister(MemoryInterface::TMR0); // Read TMR0 to trigger any side effects
    tmrVal += prescaler->step(Prescaler::TMR0);
    memoryInterface->writeRegister(MemoryInterface::TMR0, tmrVal);
}
