#pragma once

#include "pic.hpp"
#include "tui_types.hpp"

class TUI_Renderer {
public:
    void draw(const PICSnapshot& snapshot,
              SimulationState& state,
              const std::optional<uint8_t>& selectedRamAddress,
              const std::string& loadedPath,
              const std::vector<std::string>& shownFileLines,
              int asmManualScrollStart,
              bool asmManualScrollEnabled,
              int* asmRenderedStart,
              std::vector<HitBox>& hitBoxes) const;

private:
    static void drawTopBits(const PICSnapshot& snapshot, std::vector<HitBox>& hitBoxes);

    static void drawMemoryGrid(const PICSnapshot& snapshot, std::vector<HitBox>& hitBoxes, const std::optional<uint8_t>& selectedRamAddress);

    static void drawAsmPanel(const PICSnapshot& snapshot,
                             const std::vector<std::string>& fileLines,
                             int manualScrollStart,
                             bool manualScrollEnabled,
                             bool preferTopOffset,
                             int* renderedStart);

    static void drawControlPanel(const SimulationState& state, std::vector<HitBox>& hitBoxes);
    static void addBitWidget(std::vector<HitBox> &hitBoxes, int y, int x, bool value, uint8_t address, uint8_t bit);
    static void printWithColor(int y, int x, short pair, int attrs, const char *format, ...);
};
