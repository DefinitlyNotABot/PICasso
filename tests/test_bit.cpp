#include <catch2/catch.hpp>

#include "../header/memory/bit.hpp"

TEST_CASE("Bit initialisiert korrekt", "[Bit]") {
    Bit b;
    REQUIRE(b.getBit() == false);
}

TEST_CASE("Bit kann gesetzt werden", "[Bit]") {
    Bit b;

    SECTION("setBit(true)") {
        b.setBit(true);
        REQUIRE(b.getBit() == true);
    }

    SECTION("setBit(false)") {
        b.setBit(false);
        REQUIRE(b.getBit() == false);
    }
}