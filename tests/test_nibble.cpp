#include <catch2/catch.hpp>
#include "../header/memory/nibble.hpp"

TEST_CASE("Nibble default constructor initializes to 0") {
    Nibble n;
    REQUIRE(n.getNibble() == 0);
}

TEST_CASE("Nibble setNibble and getNibble") {
    Nibble n;

    SECTION("Setting all bits to 0") {
        n.setNibble(0x0);
        REQUIRE(n.getNibble() == 0x0);
    }

    SECTION("Setting all bits to 1") {
        n.setNibble(0xF);
        REQUIRE(n.getNibble() == 0xF);
    }

    SECTION("Setting random nibble values") {
        n.setNibble(0x5); // 0101
        REQUIRE(n.getNibble() == 0x5);

        n.setNibble(0xA); // 1010
        REQUIRE(n.getNibble() == 0xA);
    }
}

TEST_CASE("Nibble setBit and getBit") {
    Nibble n;

    // alle Bits auf 0
    n.setNibble(0);

    SECTION("Set individual bits to 1") {
        for (uint8_t i = 0; i < 4; ++i) {
            n.setBit(i, true);
            REQUIRE(n.getBit(i) == true);
        }
        REQUIRE(n.getNibble() == 0xF);
    }

    SECTION("Clear individual bits") {
        n.setNibble(0xF);
        for (uint8_t i = 0; i < 4; ++i) {
            n.setBit(i, false);
            REQUIRE(n.getBit(i) == false);
        }
        REQUIRE(n.getNibble() == 0x0);
    }

    SECTION("Mix of bits") {
        n.setBit(0, true);
        n.setBit(1, false);
        n.setBit(2, true);
        n.setBit(3, false);
        REQUIRE(n.getNibble() == 0b0101);
    }
}
