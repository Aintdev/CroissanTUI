#include "pch.h"

#include "ctui_container_screen.h"
#include "ctui_config.h"
#include "ctui_raw_mode.h"

namespace ctui
{
	void Screen::update_bounds(const std::pair<int, int>& winsize)
	{
		_relative_bounds = Rect(0, 0, winsize.first, winsize.second);
		_absolute_bounds = _relative_bounds;
	}

	void Screen::measure(int available_width)
	{
		auto saved_bounds = _relative_bounds;
		VStack::measure(available_width);
		_relative_bounds = saved_bounds;
	}


}
