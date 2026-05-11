#include "pch.h"
#include "ctui_config.h"

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
    bool rawMode = false;


    void enableRawMode() {
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
        rawMode = true;
    }

    void disableRawMode() {
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
        rawMode = false;
    }

    std::pair<int, int> getWindowSize() {
#ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int columns, rows;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        return std::make_pair(columns, rows);
#else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return std::make_pair(w.ws_col, w.ws_row);
#endif
    }

    CursorPos getCursorPos() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return {
            csbi.dwCursorPosition.Y + 1,  // row
            csbi.dwCursorPosition.X + 1   // col
        };
    }
}
