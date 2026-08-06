#pragma once
#include <string_view>

#include "ctui_grapheme.h"
namespace ctui
{
    class GraphemeView {
    public:
        explicit GraphemeView(std::string_view text)
            : _text(text) {
        }

        class Iterator {
        public:
            Iterator(std::string_view sv, size_t offset = 0);

            Grapheme operator*() const;
            Iterator& operator++();

            bool operator==(const Iterator& it) const;
            bool operator!=(const Iterator& it) const;

        private:
            std::string_view _text;
            size_t _offset;
        };

        Iterator begin() const;
        Iterator end() const;

    private:
        std::string_view _text;
    };

}
