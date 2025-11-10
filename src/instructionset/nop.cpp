#include "nop.hpp"

NOP::NOP(uint16_t instruction){
    
}


uint16_t NOP::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string NOP::getName()
{
    return "nop";
}

