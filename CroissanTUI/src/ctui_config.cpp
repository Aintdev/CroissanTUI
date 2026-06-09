#include "pch.h"
#include "ctui_config.h"

#include "ctui_mod.h"
#include "ctui_print.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#endif

namespace ctui {
    bool raw_mode = false;


    void enable_raw_mode() {
#ifdef _WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleMode(hOut, &mode);
        SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#else
        termios t;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag &= ~(ICANON | ECHO | IXON);
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
        raw_mode = true;
        print << "\033[2J\033[H";
    }

    void disable_raw_mode() {
#ifdef _WIN32
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
#else
        termios t;
        tcgetattr(STDIN_FILENO, &t);
        t.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
        raw_mode = false;
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
