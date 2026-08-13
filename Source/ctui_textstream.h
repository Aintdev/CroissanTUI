#pragma once

#include "ctui_defaults.h"

#include <variant>
#include <functional>
#include <vector>
#include <string>

namespace ctui
{
	struct Label;

	using TextToken = std::variant<std::string, Color, GraphicMod, std::function<std::string()>>;

    class TextStream
    {
        std::vector<TextToken> _buffer;
        bool _init = false;

        //cache handling
        mutable bool _dirty = true;
        mutable std::vector<std::string> _cached_lines;
        mutable std::vector<std::string> _cached_fn_results;
        mutable size_t _cached_available_width = 0;


        void check_if_fn_are_dirty() const;
		[[nodiscard]] std::vector<std::string> make_raw_lines_cache(size_t available_width) const;
    public:
        TextStream(const TextToken& default_string = defaults::LabelDefaults::kText);

        [[nodiscard]] bool is_init() const;

        [[nodiscard]] const std::vector<TextToken>& get_buffer() const;

        [[nodiscard]] const std::vector<std::string>& raw_lines(size_t available_width) const;
        [[nodiscard]] const std::vector<std::string>& cached_raw_lines() const;

        [[nodiscard]] const std::vector<std::string>& get_fn_result_cache() const;

        


        TextStream& operator<<(TextToken tt);
    };
}
