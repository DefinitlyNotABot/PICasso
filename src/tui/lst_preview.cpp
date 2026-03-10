#include "lst_preview.hpp"
#include "tui_helper.hpp"
#include "tui_layout.hpp"
#include <curses.h>
#include <fstream>

std::vector<std::string> LstPreview::loadFileLines(const std::string& filePath)
{
    std::vector<std::string> lines;
    if (filePath.empty())
    {
        return lines;
    }

    std::ifstream input(filePath);
    if (!input.is_open())
    {
        return lines;
    }

    std::string line;
    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        lines.push_back(line);
    }

    return lines;
}

void LstPreview::drawPreview(const std::vector<std::string>& lines,
                              int top, int left, int maxRows, int maxWidth,
                              short colorPair)
{
    if (lines.empty())
    {
        attron(COLOR_PAIR(CP_STATUS_WARN));
        mvprintw(top, left, "(empty file)");
        attroff(COLOR_PAIR(CP_STATUS_WARN));
        return;
    }

    for (int i = 0; i < maxRows && i < static_cast<int>(lines.size()); ++i)
    {
        std::string line = lines[static_cast<size_t>(i)];
        if (static_cast<int>(line.size()) > maxWidth)
        {
            line = line.substr(0, static_cast<size_t>(maxWidth));
        }
        attron(COLOR_PAIR(colorPair));
        mvprintw(top + i, left, "%s", line.c_str());
        attroff(COLOR_PAIR(colorPair));
    }
}

void LstPreview::drawAsmView(const std::vector<std::string>& lines,
                              int top, int left, int maxRows, int textWidth,
                              uint16_t programCounter,
                              int manualScrollStart, bool manualScrollEnabled,
                              bool preferTopOffset, int* renderedStart)
{
    attron(A_BOLD | COLOR_PAIR(CP_HEADER));
    mvprintw(top, left, "ASM code");
    attroff(A_BOLD | COLOR_PAIR(CP_HEADER));

    int currentFileLine = 0;
    bool foundCurrentLine = false;
    for (int i = 0; i < static_cast<int>(lines.size()); ++i)
    {
        uint16_t lstIndex = 0;
        if (TUI_Helper::parseLstInstructionIndex(lines[static_cast<size_t>(i)], lstIndex) && lstIndex == programCounter)
        {
            currentFileLine = i;
            foundCurrentLine = true;
            break;
        }
    }

    int start = 0;
    if (manualScrollEnabled)
    {
        start = TUI_Helper::clampAsmScrollStart(manualScrollStart, static_cast<int>(lines.size()));
    }
    else if (preferTopOffset)
    {
        start = TUI_Helper::findFirstCodeLineIndex(lines);
    }
    else if (foundCurrentLine && currentFileLine > 5)
    {
        start = currentFileLine - 5;
    }

    start = TUI_Helper::clampAsmScrollStart(start, static_cast<int>(lines.size()));
    if (renderedStart != nullptr)
    {
        *renderedStart = start;
    }

    for (int row = 0; row < maxRows; ++row)
    {
        int lineIndex = start + row;
        int y = top + 1 + row;
        int displayLineNumber = lineIndex + 1;

        if (lineIndex >= static_cast<int>(lines.size()))
        {
            attron(COLOR_PAIR(CP_LABEL));
            mvprintw(y, left, "%3d|", displayLineNumber);
            attroff(COLOR_PAIR(CP_LABEL));
            continue;
        }

        std::string lineText = lines[static_cast<size_t>(lineIndex)];

        uint16_t lstIndex = 0;
        const bool indexAvailable = TUI_Helper::parseLstInstructionIndex(lineText, lstIndex);
        const bool isCurrentInstruction = indexAvailable && lstIndex == programCounter;

        const char* marker = isCurrentInstruction ? ">" : " ";
        const short linePair = isCurrentInstruction ? CP_HIGHLIGHT : CP_VALUE;
        const int lineAttr = isCurrentInstruction ? A_BOLD : 0;

        int flags = lineAttr | COLOR_PAIR(linePair);
        if (flags != 0) attron(flags);
        mvprintw(y, left, "%3d%s| %-*.*s", displayLineNumber, marker, textWidth, textWidth, lineText.c_str());
        if (flags != 0) attroff(flags);
    }
}
