#pragma once

class Bit
{
private:
    bool bitValue = 0;

public:
    Bit();

    void setBit(bool value);
    bool getBit() const;
};
