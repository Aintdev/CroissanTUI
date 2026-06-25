#pragma once

#include <string>

namespace ctui
{
    /**
     * @brief Calculates the terminal display width of a UTF-8 encoded string.
     *
     * Counts the number of terminal columns the string occupies, correctly
     * handling multi-byte characters:
     * - Combining marks (diacritics etc.) contribute 0 columns.
     * - Wide characters (CJK, Hangul, most emoji) contribute 2 columns.
     * - All other codepoints contribute 1 column.
     *
     * Invalid UTF-8 byte sequences are replaced with U+FFFD (replacement
     * character) and counted as 1 column.
     *
     * @param text A UTF-8 encoded string.
     * @return The display width in terminal columns.
     */
    size_t utf8_display_width(const std::string& text);
}
