#include "pch.h"
#include "ctui_config.h"

#include "ctui_print.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <sys/ioctl.h>
#endif

namespace ctui
{
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
