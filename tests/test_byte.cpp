#include <catch2/catch.hpp>
#include "../header/memory/byte.hpp"

TEST_CASE("Byte default constructor") {
    Byte b;
    REQUIRE(b.getByte() == 0);
    REQUIRE(b.getLowNibble() == 0);
    REQUIRE(b.getHighNibble() == 0);
}

TEST_CASE("Byte setByte and getByte") {
    Byte b;
    b.setByte(0xAB);
    REQUIRE(b.getByte() == 0xAB);

    REQUIRE(b.getLowNibble() == 0xB);
    REQUIRE(b.getHighNibble() == 0xA);
}

TEST_CASE("Byte setHighNibble and setLowNibble") {
    Byte b;
    b.setByte(0x00);

    b.setHighNibble(0xF);
    REQUIRE(b.getHighNibble() == 0xF);
    REQUIRE(b.getLowNibble() == 0x0); // low nibble sollte unverändert bleiben

    b.setLowNibble(0x5);
    REQUIRE(b.getLowNibble() == 0x5);
    REQUIRE(b.getHighNibble() == 0xF);
}

TEST_CASE("Byte setBit and getBit") {
    Byte b;
    b.setByte(0x00);

    // Low nibble bits
    b.setBit(0, true);
    b.setBit(3, true);
    REQUIRE(b.getBit(0) == true);
    REQUIRE(b.getBit(1) == false);
    REQUIRE(b.getBit(3) == true);

    // High nibble bits
    b.setBit(4, true);
    b.setBit(7, true);
    REQUIRE(b.getBit(4) == true);
    REQUIRE(b.getBit(5) == false);
    REQUIRE(b.getBit(7) == true);

    // Gesamtbyte prüfen
    REQUIRE(b.getByte() == 0x99); // 1001 1001
}
