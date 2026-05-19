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
        CYAN, WHITE, DEFAULT = 9
    };
    constexpr int fg_base = 30;
    constexpr int bg_base = 40;

}