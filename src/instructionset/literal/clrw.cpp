#include "clrw.hpp"

CLRW::CLRW(uint16_t instruction){
    
}


uint16_t CLRW::execute()
{
    W->writeByte(0);
    SET_ZERO_FLAG_W
    return 1;
}

std::string CLRW::getName()
{
    return "clrw";
}

