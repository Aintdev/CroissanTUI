#pragma once
#include <utility>

namespace ctui {
    struct CursorPos { int row, col; };
    extern bool rawMode;
    void enableRawMode();
    void disableRawMode();
    std::pair<int, int> getWindowSize();
}