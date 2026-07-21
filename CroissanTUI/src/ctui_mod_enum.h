#pragma once
namespace ctui {
    enum class GraphicMod {
        RESET_ALL = 0, BOLD = 1, DIM = 2,
        ITALIC = 3, UNDERLINE = 4, BLINK = 5,
        REVERSE = 6, INVISIBLE = 7, STRIKE = 8
    };
    enum class Color {
        BLACK = 0, RED, GREEN,
        YELLOW, BLUE, MAGENTA,
        CYAN, WHITE,

        FG_BLACK = 30, FG_RED, FG_GREEN,
        FG_YELLOW, FG_BLUE, FG_MAGENTA,
        FG_CYAN, FG_WHITE,

        BG_BLACK = 40, BG_RED, BG_GREEN,
        BG_YELLOW, BG_BLUE, BG_MAGENTA,
        BG_CYAN, BG_WHITE,
    };

    enum class Align { Start, Center, End };
}