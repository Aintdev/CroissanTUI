#include "pch.h"

#include "ctui_raw_mode.h"

namespace ctui
{
    RawModeGuard::RawModeGuard()
    {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        _stdin = GetStdHandle(STD_INPUT_HANDLE);
        _stdout = GetStdHandle(STD_OUTPUT_HANDLE);

        // GetConsoleMode fails if the handle is invalid or redirected (e.g. stdin/stdout
        // piped to a file). Without this check, _original_*_mode stays uninitialized and
        // we'd later restore garbage in the destructor.
        if (!GetConsoleMode(_stdin, &_original_stdin_mode))
            throw std::system_error(GetLastError(), std::system_category(), "GetConsoleMode (stdin) failed");

        if (!GetConsoleMode(_stdout, &_original_stdout_mode))
            throw std::system_error(GetLastError(), std::system_category(), "GetConsoleMode (stdout) failed");

        DWORD stdin_mode = _original_stdin_mode;
        stdin_mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
        if (!SetConsoleMode(_stdin, stdin_mode))
        {
            reset_to_original();
            throw std::system_error(GetLastError(), std::system_category(), "SetConsoleMode (stdin) failed");
        }

        DWORD stdout_mode = _original_stdout_mode;
        stdout_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(_stdout, stdout_mode)) 
        {
            reset_to_original();
            throw std::system_error(GetLastError(), std::system_category(), "SetConsoleMode (stdout) failed");
        }
#else
        // Same reasoning as GetConsoleMode above: tcgetattr fails for non-TTY stdin
        // (redirected/piped), and leaves _original untouched on failure.
        if (tcgetattr(STDIN_FILENO, &_original) != 0)
            throw std::system_error(errno, std::generic_category(), "tcgetattr failed");

        termios raw = _original;
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_iflag &= ~IXON;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1)
            throw std::system_error(errno, std::generic_category(), "tcsetattr failed");
#endif
        std::ios::sync_with_stdio(false);
        std::cout << "\033[?1049h\033[2J\033[H\033[?25l";
    }

    RawModeGuard::~RawModeGuard()
    {
        // Must run *before* restoring the console mode below: if the original stdout
        // mode didn't have ENABLE_VIRTUAL_TERMINAL_PROCESSING (the common case), the
        // escape sequence would no longer be interpreted once we restore it, and the
        // terminal would be stuck in the alternate screen buffer.
        std::cout << "\033[?1049l\033[?25h" << std::flush;

        reset_to_original();
    }

    void RawModeGuard::reset_to_original()
    {
#ifdef _WIN32
        SetConsoleMode(_stdin, _original_stdin_mode);
        SetConsoleMode(_stdout, _original_stdout_mode);
#else
        tcsetattr(STDIN_FILENO, TCSANOW, &_original);
#endif
    }
}
