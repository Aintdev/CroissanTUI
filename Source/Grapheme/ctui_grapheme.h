#pragma once
#include <string_view>

namespace ctui
{
	struct Grapheme {
		std::string_view text;

		/**
		 * calculates visible length in terminal
		 * @return width of grapheme in terminal
		 */
		size_t terminal_width() const;

		/**
		 * gets allocated bytes of grapheme
		 * @return size in memory of grapheme
		 */
		size_t byte_count() const;
	};
}
