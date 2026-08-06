#pragma once
#include <string_view>

namespace ctui
{
	struct Grapheme {
		std::string_view text;
		size_t terminal_width() const;
		size_t byte_count() const;
	};
}
