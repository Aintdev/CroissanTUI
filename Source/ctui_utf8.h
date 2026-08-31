#pragma once

#include <string>

namespace ctui
{
	/**
	 * The utf8_display_width function calculates the display width of 
	 * a UTF-8 encoded string by summing the terminal widths of its graphemes.
	 * @param text The text to calculate the width from
	 * @return Width of text in Terminal
	 */
	size_t utf8_display_width(const std::string_view text);

    /**
     * Calculates ANSI Escape Sequences to move cursor to given coordinates.
     * @param x X-Position to move to
     * @param y Y-Position to move to
     * @return ANSI Escape Sequences as std::string
     */
    std::string mv_cursor(const size_t x, const size_t y);
}
