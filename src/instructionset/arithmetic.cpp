#include "arithmetic.hpp"


uint16_t Arithmetic::getDestination(){
    return destination;
}

uint16_t Arithmetic::getFile(){
    return file;
}

void Arithmetic::storeResult(uint16_t result) {

    if(destination == 0) {
        W->writeByte(result & 0xFF);
    } else {
        memoryInterface->writeRegister(file, result & 0xFF);
    }
}

void Arithmetic::loadCurrentValues() {
    fileValue = memoryInterface->readRegister(file);
    WValue = W->readByte();
}

