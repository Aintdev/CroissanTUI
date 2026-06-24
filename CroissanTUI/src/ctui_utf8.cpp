#include "pch.h"
#include "ctui_utf8.h"

#include <string>
#include <cstdint>

static bool is_continuation_byte(unsigned char c)
{
    return (c & 0xC0) == 0x80;
}

// very small check for combining marks (basic Unicode range)
static bool is_combining(uint32_t cp)
{
    return (cp >= 0x300 && cp <= 0x36F) ||   // diacritics
        (cp >= 0x1AB0 && cp <= 0x1AFF) ||
        (cp >= 0x1DC0 && cp <= 0x1DFF) ||
        (cp >= 0x20D0 && cp <= 0x20FF) ||
        (cp >= 0xFE20 && cp <= 0xFE2F);
}

// decode one UTF-8 codepoint
static uint32_t next_codepoint(const char*& s)
{
    unsigned char c = (unsigned char)*s++;

    if (c < 0x80) return c;

    if ((c & 0xE0) == 0xC0)
    {
        uint32_t cp = (c & 0x1F) << 6;
        cp |= (*s++ & 0x3F);
        return cp;
    }

    if ((c & 0xF0) == 0xE0)
    {
        uint32_t cp = (c & 0x0F) << 12;
        cp |= (*s++ & 0x3F) << 6;
        cp |= (*s++ & 0x3F);
        return cp;
    }

    if ((c & 0xF8) == 0xF0)
    {
        uint32_t cp = (c & 0x07) << 18;
        cp |= (*s++ & 0x3F) << 12;
        cp |= (*s++ & 0x3F) << 6;
        cp |= (*s++ & 0x3F);
        return cp;
    }

    return 0xFFFD; // invalid
}

// main function
size_t utf8_grapheme_width(const std::string& text)
{
    size_t width = 0;

    const char* s = text.c_str();

    while (*s)
    {
        const char* prev = s;
        uint32_t cp = next_codepoint(s);

        if (cp == 0)
            continue;

        // skip combining marks (attach to previous char)
        if (is_combining(cp))
            continue;

        // rough emoji / CJK width handling
        if (
            (cp >= 0x1100 && cp <= 0x115F) ||  // Hangul Jamo
            (cp >= 0x2E80 && cp <= 0xA4CF) ||  // CJK
            (cp >= 0xAC00 && cp <= 0xD7A3) ||  // Hangul syllables
            (cp >= 0x1F300 && cp <= 0x1FAFF)   // emojis
            )
        {
            width += 2;
        }
        else
        {
            width += 1;
        }
    }

    return width;
}