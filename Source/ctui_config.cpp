#include "pch.h"
#include "ctui_config.h"

#include <csignal>

#include "ctui_print.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif

namespace 
{
    volatile std::sig_atomic_t running = 0;
    volatile std::sig_atomic_t signal_status = 0;
}

namespace ctui
{
    bool get_running()
    {
        return running;
    }

    void set_running(bool x)
    {
        running = x;
    }

    void reset_signal()
    {
        signal_status = 0;
    }

    int get_signal_status()
    {
        return signal_status;
    }

    void signal_handler(int sig)
    {
        running = 0;
        signal_status = sig;
    }

    std::pair<int, int> get_win_size() {
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        const int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        const int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return std::make_pair(columns, rows);
#else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return std::make_pair(w.ws_col, w.ws_row);
#endif
    }
}
