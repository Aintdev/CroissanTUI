#include "pch.h"
#include "ctui_widget_label.h"

#include "ctui_print.h"
#include "ctui_utf8.h"

namespace ctui
{
	bool Label::input(Key key)
	{
		return false;
	}

	void Label::measure()
	{
		int width = 0;
		for (const std::string& line : _lines)
		{
			width = std::max(width, static_cast<int>(utf8_display_width(line))); //TODO: bug here cause it counts bytes not chars and not every char is one byte long.
		}

		_relative_bounds = Rect(
			width,
			static_cast<int>(_lines.size())
		);
	}

	void Label::resolve_bounds(int startx, int starty)
	{
		_absolute_bounds = Rect(
			(_relative_bounds.x.value_or(0) + startx),
			(_relative_bounds.y.value_or(0) + starty),
			_relative_bounds.width.value(),
			_relative_bounds.height.value()
		);
	}
	
	void Label::render()
	{
		if (!_absolute_bounds.x.has_value() || !_absolute_bounds.y.has_value() || !_absolute_bounds.has_size_values())
		{
			throw std::runtime_error("_absolute_bounds has not been initialized. Please call resolve_bounds() before render.");
		}

		for (size_t y_offset = 0; y_offset < _lines.size(); y_offset++)
		{
			const std::string& line = _lines[y_offset];

			const int len = static_cast<int>(utf8_display_width(line));
			
			int x_offset = 0;

			if (_halign == Align::Center)
			{
				x_offset = _relative_bounds.width.value() / 2 - len / 2;
			} 
			else if (_halign == Align::End)
			{
				x_offset = _relative_bounds.width.value() - len;
			}

			print << Mod::mv_cur(_absolute_bounds.x.value() + x_offset, _absolute_bounds.y.value() + static_cast<int>(y_offset)) << line;
		}
	}
}
