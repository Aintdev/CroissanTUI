#pragma once
#include <csignal>
#include <utility>

namespace ctui {
    bool get_running();
    void set_running(bool x);
    int get_signal_status();
    void reset_signal();

    void signal_handler(int sig);

    std::pair<int, int> get_win_size();
}