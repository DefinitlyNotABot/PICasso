#pragma once
#include "tui_types.hpp"

class TUI_Helper {
    public:
        static bool isInAsmPanel(int y, int x);

        static int clampAsmScrollStart(int scrollStart, int totalLines);

        static bool contains(const HitBox &hit, int y, int x);
        static std::optional<std::string> promptInput(const std::string &prompt);
        static void setStatus(SimulationState &state, const std::string &message);
        static bool parseHexByte(const std::string &text, uint8_t &output);
        static std::string toHex2(uint8_t value);
};
