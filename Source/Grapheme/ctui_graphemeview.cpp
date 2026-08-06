#include "pch.h"
#include "ctui_graphemeview.h"

extern "C" {
#include <grapheme.h>
}

namespace ctui
{
    GraphemeView::Iterator::Iterator(std::string_view sv, size_t offset)
        : _text(sv), _offset(offset) {
    }

    Grapheme GraphemeView::Iterator::operator*() const
    {
        size_t len = grapheme_next_character_break_utf8(
            _text.data() + _offset,
            _text.size() - _offset);

        return {
            std::string_view(_text.data() + _offset, len)
        };
    }

    GraphemeView::Iterator& GraphemeView::Iterator::operator++()
    {
        _offset += grapheme_next_character_break_utf8(
            _text.data() + _offset,
            _text.size() - _offset);

        return *this;
    }

    bool GraphemeView::Iterator::operator==(const Iterator& it) const
    {
        return _offset == it._offset;
    }

    bool GraphemeView::Iterator::operator!=(const Iterator& it) const
    {
        return _offset != it._offset;
    }

    GraphemeView::Iterator GraphemeView::begin() const
    {
        return { _text };
    }

    GraphemeView::Iterator GraphemeView::end() const
    {
        return { _text, _text.size() };
    }

}
