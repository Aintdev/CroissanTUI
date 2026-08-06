#include "pch.h"
#include "ctui_utf8.h"

#include <string>

#include "Grapheme/ctui_grapheme.h"
#include "Grapheme/ctui_graphemeview.h"

namespace ctui
{
    size_t utf8_display_width(std::string_view text)
    {
        size_t width = 0;

        for (Grapheme g : GraphemeView(text))
            width += g.terminal_width();
        return width;
    }

    std::string mv_cursor(const size_t x, const size_t y)
    {
        return std::string("\033[") + std::to_string(y) + ";" + std::to_string(x) + "f";
    }
}

