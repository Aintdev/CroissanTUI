#include "pch.h"

#include <climits>

#include "ctui_textstream.h"

#include "Grapheme/ctui_graphemeview.h"
#include "Widgets/ctui_widget_label.h"
#include "Widgets/Container/ctui_container_screen.h"

namespace
{
	void add_lines_with_wrapping(std::vector<std::string>& lines, std::string_view sv, const size_t available_width)
	{
		size_t visible_chars = 0;

		lines.emplace_back("");
		size_t index = lines.size() - 1;
		
		for (ctui::Grapheme grapheme : ctui::GraphemeView(sv))
		{
			if (grapheme.terminal_width() + visible_chars > available_width)
			{
				lines.emplace_back("");
				visible_chars = 0;
				index++;
			}
			lines[index] += grapheme.text;
			visible_chars += grapheme.terminal_width();
		}
		//debug_print_lines(lines);
	}
}

namespace ctui
{
	TextStream::TextStream(const TextToken& default_string)
	{
		_buffer.emplace_back(default_string);
	}

	bool TextStream::is_init() const
	{
		return _init;
	}

	const std::vector<TextToken>& TextStream::get_buffer() const
	{
		return _buffer;
	}

	TextStream& TextStream::operator<<(TextToken tt)
	{
		_dirty = true;
		if (!is_init())
		{
			_buffer.clear();
			_init = true;
		}
		_buffer.emplace_back(std::move(tt));
		return *this;
	}

	void TextStream::check_if_fn_are_dirty() const
	{
		size_t index = 0;
		for (const auto& tt : _buffer)
		{
			if (const auto* fn = std::get_if<std::function<std::string()>>(&tt))
			{
				if (_cached_fn_results.size() > index && _cached_fn_results[index] != (*fn)())
				{
					_dirty = true;
					break;
				}

				index++;
			}
		}
	}

	std::vector<std::string> TextStream::make_raw_lines_cache(const size_t available_width) const
	{
		std::vector<std::string> lines;
		std::string buff;
		size_t start = 0; // index in buff where the current (not-yet-terminated) line begins
		_cached_fn_results.clear();
		for (const TextToken& tt : get_buffer())
		{
			if (const auto* s = std::get_if<std::string>(&tt))
			{
				// token holds a plain string piece -> append as-is
				buff += *s;
			}
			else if (const auto* fn = std::get_if<std::function<std::string()>>(&tt))
			{
				// token holds a lazy/dynamic piece -> invoke it to get the text
				buff += (*fn)();
				_cached_fn_results.emplace_back((*fn)());

			}
			else continue; // token variant holds neither alternative (e.g. monostate) -> skip

			// insert buff into lines if '\n' is present

			while (true)
			{
				// search only from 'start' onward, since everything before was
				// already split off into 'lines' in a previous iteration/token
				const size_t end = buff.find('\n', start);

				if (end == std::string::npos)
				{
					// no more complete lines in what we have so far;
					// remaining partial line stays in buff until more tokens arrive
					break;
				}

				// This only runs if current token has a line ending >>

				add_lines_with_wrapping(lines, buff.substr(start, end - start), available_width);
				//lines.emplace_back(buff.substr(start, end - start)); //old code

				start = end + 1; // move past the '\n' we just consumed
			}
		}

		// whatever is left after the last '\n' (or the whole buffer, if none was found)
		// is a final line with no trailing newline
		if (start <= buff.size()) add_lines_with_wrapping(lines, buff.substr(start), available_width);

		for (auto& line : lines)
		{
			if (!line.empty() && line.back() == '\r')
				line.pop_back(); // strip CR so CRLF (\r\n) line endings become plain lines
		}

		return lines;
	}

	const std::vector<std::string>& TextStream::raw_lines(size_t available_width) const
	{
		// check all std::function<...> TextTokens if they're dirty.
		check_if_fn_are_dirty();

		if (available_width == INT_MAX)
			available_width = screen.get_bounds().first;

		if (_dirty || _cached_available_width != available_width)
		{
			_cached_lines = make_raw_lines_cache(available_width);
			_cached_available_width = available_width;
			_dirty = false;
		}

		return _cached_lines;
	}

	const std::vector<std::string>& TextStream::cached_raw_lines() const 
	{
		return _cached_lines;
	}
}
