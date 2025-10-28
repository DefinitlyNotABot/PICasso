# include "../header/ram.hpp"

Ram::Ram()
{
    // need to look up what registrys need to be initialized
}

uint8_t Ram::getRegister(uint8_t address)
{
    return memory[address].getValue();
}

void Ram::setRegister(uint8_t address, uint8_t value)
{
    memory[address].setByte(value);
}