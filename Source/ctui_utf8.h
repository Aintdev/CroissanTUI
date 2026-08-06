#pragma once

#include <string>

namespace ctui
{
    size_t utf8_display_width(const std::string_view text);

    /// <summary>
    /// Moves cursor to given coordinates.
    /// </summary>
    /// <param name="x">X-Position to move to</param> 
    /// <param name="y">Y-Position to move to</param>
    std::string mv_cursor(const size_t x, const size_t y);
}
