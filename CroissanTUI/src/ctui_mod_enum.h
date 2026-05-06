#pragma once
namespace ctui {
    enum class GRAPHIC_MOD {
        RESET_ALL = 0, BOLD = 1, DIM = 2,
        ITALIC = 3, UNDERLINE = 4, BLINK = 5,
        REVERSE = 6, INVISIBLE = 7, STRIKE = 8
    };
    namespace color {
        enum class FG {
            BLACK = 30, RED, GREEN,
            YELLOW, BLUE, MAGENTA,
            CYAN, WHITE, DEFAULT = 39
        };
        enum class BG {
            BLACK = 40, RED, GREEN,
            YELLOW, BLUE, MAGENTA,
            CYAN, WHITE, DEFAULT = 49
        };
    }
}