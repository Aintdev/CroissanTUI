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
		if (!is_init())
		{
			_buffer.clear();
			_init = true;
		}
		_buffer.emplace_back(std::move(tt));
		return *this;
	}

	std::vector<std::string> TextStream::raw_lines() const
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
}