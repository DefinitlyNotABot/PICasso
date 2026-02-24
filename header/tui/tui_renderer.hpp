#pragma once

#include "tui_types.hpp"
#include "tui_shareddata.hpp"
#include <memory>

class TUI_Renderer {
public:
    TUI_Renderer(std::shared_ptr<TUI_SharedData> sharedDataIn);
    void draw(SimulationState& state,
              const std::string& loadedPath,
              std::vector<HitBox>& hitBoxes) const;

private:
    std::shared_ptr<TUI_SharedData> sharedData;

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
