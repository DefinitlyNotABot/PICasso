#include <catch2/catch.hpp>
#include "../header/ram.hpp"
#include <stdexcept>

#define STATUS_REGISTER_ADDRESS 0x03

TEST_CASE("Ram reset initializes memory correctly", "[Ram]") {
    Ram ram;

    SECTION("Memory at 0x03 has bits 3 and 4 set") {
        uint8_t reg03 = ram.readRegister(0x03);
        REQUIRE((reg03 & (1 << 3)) != 0);
        REQUIRE((reg03 & (1 << 4)) != 0);
    }

    SECTION("Memory at 0x83 has bits 3 and 4 set") {
        uint8_t reg83 = ram.readRegister(0x03, true);
        REQUIRE((reg83 & (1 << 3)) != 0);
        REQUIRE((reg83 & (1 << 4)) != 0);
    }

    SECTION("Memory at 0x85 is 0x1F") {
        REQUIRE(ram.readRegister(0x05, true) == 0x1F);
    }

    SECTION("Memory at 0x86 is 0xFF") {
        REQUIRE(ram.readRegister(0x06, true) == 0xFF);
    }

    SECTION("Memory at 0x81 is 0xFF") {
        ram.writeBit(STATUS_REGISTER_ADDRESS, 5, true);
        REQUIRE(ram.readRegister(0x01) == 0xFF);
        ram.writeBit(STATUS_REGISTER_ADDRESS, 5, false);
    }
}

TEST_CASE("Read and write registers", "[Ram]") {
    Ram ram;

    SECTION("Writing and reading back a byte works") {
        ram.writeRegister(0x10, 0xAB);
        REQUIRE(ram.readRegister(0x10) == 0xAB);
    }

    SECTION("Writing multiple registers independently") {
        ram.writeRegister(0x20, 0x12);
        ram.writeRegister(0x21, 0x34);
        REQUIRE(ram.readRegister(0x20) == 0x12);
        REQUIRE(ram.readRegister(0x21) == 0x34);
    }
}
