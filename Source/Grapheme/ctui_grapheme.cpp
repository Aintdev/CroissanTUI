#include "pch.h"
#include "ctui_grapheme.h"

#include <utf8proc.h>

namespace ctui
{
    size_t Grapheme::byte_count() const
    {
        return text.size();
    }

    size_t Grapheme::terminal_width() const
    {
        constexpr utf8proc_int32_t kVS15 = 0xFE0E; // force text presentation (narrow)
        constexpr utf8proc_int32_t kVS16 = 0xFE0F; // force emoji presentation (wide)

        const auto* data = reinterpret_cast<const utf8proc_uint8_t*>(text.data());
        utf8proc_ssize_t remaining = static_cast<utf8proc_ssize_t>(text.size());
        utf8proc_ssize_t offset = 0;

        size_t width = 0;
        bool has_vs16 = false;
        bool has_vs15 = false;

        while (offset < remaining)
        {
            utf8proc_int32_t codepoint;
            utf8proc_ssize_t len = utf8proc_iterate(
                data + offset,
                remaining - offset,
                &codepoint
            );
            if (len <= 0)
                break; // malformed input, bail out

            if (codepoint == kVS16)
                has_vs16 = true;
            else if (codepoint == kVS15)
                has_vs15 = true;
            else
                width = std::max<size_t>(width, static_cast<size_t>(utf8proc_charwidth(codepoint)));

            offset += len;
        }

        if (has_vs16)
            return 2; // explicit emoji presentation always wins
        if (has_vs15)
            return 1; // explicit text presentation always wins

        return width;
    }
}