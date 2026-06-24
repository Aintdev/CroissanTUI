#include "pch.h"
#include "ctui_utf8.h"

#include <cstdint>
#include <string>

namespace
{
    bool is_combining(const uint32_t cp)
    {
        return (cp >= 0x0300 && cp <= 0x036F) || // Combining Diacritical Marks
            (cp >= 0x1AB0 && cp <= 0x1AFF) ||
            (cp >= 0x1DC0 && cp <= 0x1DFF) ||
            (cp >= 0x20D0 && cp <= 0x20FF) ||
            (cp >= 0xFE20 && cp <= 0xFE2F);
    }

    uint32_t next_codepoint(const char*& s)
    {
        const unsigned char c = static_cast<unsigned char>(*s++);

        if (c < 0x80)
            return c;

        if ((c & 0xE0) == 0xC0)
        {
            uint32_t cp = (c & 0x1F) << 6;
            cp |= (static_cast<unsigned char>(*s++) & 0x3F);
            return cp;
        }

        if ((c & 0xF0) == 0xE0)
        {
            uint32_t cp = (c & 0x0F) << 12;
            cp |= (static_cast<unsigned char>(*s++) & 0x3F) << 6;
            cp |= (static_cast<unsigned char>(*s++) & 0x3F);
            return cp;
        }

        if ((c & 0xF8) == 0xF0)
        {
            uint32_t cp = (c & 0x07) << 18;
            cp |= (static_cast<unsigned char>(*s++) & 0x3F) << 12;
            cp |= (static_cast<unsigned char>(*s++) & 0x3F) << 6;
            cp |= (static_cast<unsigned char>(*s++) & 0x3F);
            return cp;
        }

        return 0xFFFD; // Replacement Character
    }

    bool is_wide_character(const uint32_t cp)
    {
        return
            (cp >= 0x1100 && cp <= 0x115F) || // Hangul Jamo
            (cp >= 0x2E80 && cp <= 0xA4CF) || // CJK, Yi, Radicals
            (cp >= 0xAC00 && cp <= 0xD7A3) || // Hangul Syllables
            (cp >= 0x1F300 && cp <= 0x1FAFF); // Most emoji blocks
    }
}

namespace ctui
{
    size_t utf8_display_width(const std::string& text)
    {
        size_t width = 0;

        const char* s = text.c_str();

        while (*s)
        {
            const uint32_t cp = next_codepoint(s);

            if (is_combining(cp))
                continue;

            width += is_wide_character(cp) ? 2 : 1;
        }

        return width;
    }
}