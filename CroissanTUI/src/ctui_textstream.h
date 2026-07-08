#pragma once

#include "ctui_mod.h"
#include "ctui_defaults.h"

#include <variant>
#include <functional>
#include <vector>
#include <string>

namespace ctui
{
    using TextToken = std::variant<std::string, Mod, std::function<std::string()>>;

    class TextStream
    {
        std::vector<TextToken> _buffer;
        bool _init = false;
    public:
        TextStream(const TextToken& default_string = defaults::kText);

        [[nodiscard]] bool is_init() const;

        [[nodiscard]] const std::vector<TextToken>& get_buffer() const;

        [[nodiscard]] std::vector<std::string> raw_lines() const;

        TextStream& operator<<(const TextToken& tt);
    };
}