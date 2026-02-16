#include "clrwdt.hpp"

CLRWDT::CLRWDT(uint16_t instruction){
    
}


uint16_t CLRWDT::execute()
{
    //TODO: Implement prescaler reset and WDT timer reset
    return 0;
}

std::string CLRWDT::getName()
{
    return "clrwdt";
}

