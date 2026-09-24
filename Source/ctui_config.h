#pragma once
#include <utility>

namespace ctui {
    bool get_running();
    void set_running(bool x);
    int get_signal_status();
    void reset_signal();

    /**
     * Default signal handler of CroissanTUI. Will set ctui::running
     * to false and update signal_status.
     * 
     * Does not kill a program directly.
     * @param sig signal
     */
    void signal_handler(int sig);

    /**
     * Returns terminal size.
     * @return Windows size as pair in x, y.
     */
    std::pair<int, int> get_win_size();
}