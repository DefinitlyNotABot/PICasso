#include <curses.h>

#include "tui_initializer.hpp"
#include "tui_types.hpp"

TUIInitializer::TUIInitializer()
{
}

TUIInitializer::~TUIInitializer()
{

}

void TUIInitializer::initializeColors()
{
    if (!has_colors())
    {
        gHasColors = false;
        return;
    }

    start_color();
    use_default_colors();

    init_pair(CP_HEADER, COLOR_CYAN, -1);
    init_pair(CP_LABEL, COLOR_YELLOW, -1);
    init_pair(CP_VALUE, COLOR_WHITE, -1);
    init_pair(CP_BUTTON, COLOR_CYAN, -1);
    init_pair(CP_BUTTON_ACTIVE, COLOR_GREEN, -1);
    init_pair(CP_BUTTON_DANGER, COLOR_RED, -1);
    init_pair(CP_STATUS_OK, COLOR_GREEN, -1);
    init_pair(CP_STATUS_WARN, COLOR_YELLOW, -1);
    init_pair(CP_STATUS_ERR, COLOR_RED, -1);
    init_pair(CP_HIGHLIGHT, COLOR_MAGENTA, -1);
    init_pair(CP_INVALID, COLOR_BLUE, -1);
    init_pair(CP_BIT_ON, COLOR_GREEN, -1);
    init_pair(CP_BIT_OFF, COLOR_RED, -1);
    init_pair(CP_SELECTED_FIELD, COLOR_BLACK, COLOR_WHITE);

    gHasColors = true;
}

void TUIInitializer::initialize()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);

    initializeColors();
}