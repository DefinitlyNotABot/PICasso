#include "arithmetic.hpp"


uint8_t Arithmetic::getDestination(){
    return destination;
}

uint8_t Arithmetic::getFile(){
    return file;
}

void Arithmetic::storeResult(uint16_t result) {
    if(destination == 0) {
        W->writeByte(result & 0xFF);
    } else {
        memoryInterface->writeRegister(loadAddress(file), result & 0xFF);
    }
}

void Arithmetic::loadCurrentValues() {
    uint8_t fileOverride = loadAddress(file);
    uint8_t targetFile = fileOverride != 0xff ? fileOverride : file;
    fileValue = memoryInterface->readRegister(targetFile);
    WValue = W->readByte();
}
