#pragma once
#include <utility>

namespace ctui {
    extern bool raw_mode;
    void enable_raw_mode();
    void disable_raw_mode();
    std::pair<int, int> get_win_size();
}