#include "nop.hpp"

NOP::NOP(uint16_t instruction){
    
}


uint16_t NOP::execute()
{
    return 0;
}

std::string NOP::getName()
{
    return "nop";
}

