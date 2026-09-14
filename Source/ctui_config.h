#pragma once
#include <csignal>
#include <utility>

namespace ctui {
    extern volatile std::sig_atomic_t running;
    extern volatile bool ready;

    std::pair<int, int> get_win_size();
}