#include "retfie.hpp"

RETFIE::RETFIE(uint16_t instruction){
    
}



uint16_t RETFIE::execute()
{
    timer->timeStep();
    return 0;
}

std::string RETFIE::getName()
{
    return "retfie";
}

