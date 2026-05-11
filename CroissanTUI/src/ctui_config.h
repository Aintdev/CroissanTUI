#pragma once
#include <utility>

namespace ctui {
    extern bool rawMode;
    void enableRawMode();
    void disableRawMode();
    std::pair<int, int> getWindowSize();
}