#include "pch.h"
#include "ctui_text.h"

namespace ctui
{
	std::vector<std::string> str_to_lines(const std::string& raw)
	{
		std::vector<std::string> lines;
		size_t start = 0;
		while (true)
		{
			const size_t end = raw.find('\n', start);

			if (end == std::string::npos)
			{
				lines.emplace_back(raw.substr(start));
				return lines;
			}

			lines.emplace_back(raw.substr(start, end - start));
			start = end + 1;
		}
	}
}
