#pragma once
#include <csignal>
#include <utility>

namespace ctui {
    extern volatile std::sig_atomic_t running;
    extern volatile std::sig_atomic_t signal_status;

    void signal_handler(int sig);

    std::pair<int, int> get_win_size();
}