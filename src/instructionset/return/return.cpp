#include "return.hpp"

RETURN::RETURN(uint16_t instruction){
    
}

uint16_t RETURN::execute()
{
    uint8_t returnAddress = memoryInterface->popFromStack();
    memoryInterface->setProgramCounter(returnAddress);
    return 0;
}

std::string RETURN::getName()
{
    return "return";
}

