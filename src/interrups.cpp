#include "interrupts.hpp"

void Interrupts::checkINTCON()
{
    uint8_t intconValue = memoryInterface->readRegister(INTCON_REGISTER);
    this->flags = *reinterpret_cast<InterruptFlags *>(&intconValue);
}

void Interrupts::gotInterrupted()
{
    memoryInterface->writeBit(INTCON_REGISTER, GIE_BIT, 0);
    memoryInterface->pushToStack(memoryInterface->getProgramCounter());
    memoryInterface->setProgramCounter(0x04);
}

Interrupts::Interrupts()
{
}

Interrupts::Interrupts(std::shared_ptr<MemoryInterface> memoryInterface) : memoryInterface(memoryInterface)
{
}

Interrupts::~Interrupts()
{
}

uint8_t Interrupts::checkInterrupts()
{
    checkINTCON();

    if (flags.GIE)
    {
        if (flags.EEIE)
        {
        }
        if (flags.T0IE & flags.T0IF)
        {
            gotInterrupted();
        }
        if (flags.INTE & flags.INTF)
        {
            gotInterrupted();
        }
        if (flags.RBIE & flags.RBIF)
        {
            gotInterrupted();
        }
    }
}