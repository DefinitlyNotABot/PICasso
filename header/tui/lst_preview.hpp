#pragma once

#include "tui_types.hpp"
#include <string>
#include <vector>

class LstPreview {
public:
    static std::vector<std::string> loadFileLines(const std::string& filePath);

    static void drawPreview(const std::vector<std::string>& lines,
                            int top, int left, int maxRows, int maxWidth,
                            short colorPair);

    static void drawAsmView(const std::vector<std::string>& lines,
                            int top, int left, int maxRows, int textWidth,
                            uint16_t programCounter,
                            int manualScrollStart, bool manualScrollEnabled,
                            bool preferTopOffset, int* renderedStart);
};
