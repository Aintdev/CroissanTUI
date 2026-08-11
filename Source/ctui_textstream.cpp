#include "pch.h"

#include "ctui_textstream.h"

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
				if (_cached_fn_results[index] != (*fn)())
				{
					_dirty = true;
					break;
				}

				index++;
			}
		}
	}

	std::vector<std::string> TextStream::make_raw_lines_cache(const Label& caller) const
	{
		std::vector<std::string> lines;
		std::string buff;
		size_t start = 0;

		for (const TextToken& tt : get_buffer())
		{
			if (const auto* s = std::get_if<std::string>(&tt))
			{
				buff += *s;
			}
			else if (const auto* fn = std::get_if<std::function<std::string()>>(&tt))
			{
				buff += (*fn)();
			}
			else continue;

			// insert buff into lines if '\n' is present

			while (true)
			{
				const size_t end = buff.find('\n', start);

				if (end == std::string::npos)
				{
					break;
				}

				lines.emplace_back(buff.substr(start, end - start));
				start = end + 1;
			}
		}

		if (start <= buff.size()) lines.emplace_back(buff.substr(start));

		for (auto& line : lines)
			if (!line.empty() && line.back() == '\r')
				line.pop_back();


		return lines;
	}

	const std::vector<std::string>& TextStream::raw_lines(const Label& caller) const
	{
		// check all std::function<...> TextTokens if they're dirty.
		check_if_fn_are_dirty();
		if (_dirty)
		{
			_cached_lines = make_raw_lines_cache(caller);
			_dirty = false;
		}

		return _cached_lines;
	}
}