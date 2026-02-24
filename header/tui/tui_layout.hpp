#pragma once

class TUI_Layout {
    public:
        static const int kAsmPanelLeft = 32;
        static const int kAsmTextWidth = 80;
        static const int kAsmLinePrefixWidth = 6; // "%3d%s| "
        static const int kAsmPanelTop = 9;
        static const int kAsmVisibleRows = 20;
        static const int kAsmPanelRight = kAsmPanelLeft + kAsmLinePrefixWidth + kAsmTextWidth - 1;
        static const int kControlPanelLeft = kAsmPanelRight + 3;
        static const int kControlPanelContentLeft = kControlPanelLeft + 13;
        static const int kRequiredTerminalWidth = kControlPanelContentLeft + 22;
        static const int kRequiredTerminalHeight = 33;

};