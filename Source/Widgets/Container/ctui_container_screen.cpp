#include "pch.h"

#include "ctui_container_screen.h"
#include "ctui_config.h"

namespace ctui
{
	Screen::Screen() : VStack()
	{
		update_bounds();
	}

	void Screen::update_bounds()
	{
		const auto [fst, snd] = get_win_size();
		_relative_bounds = Rect(0, 0, fst, snd);
		_absolute_bounds = _relative_bounds;
	}

	std::pair<int, int> Screen::get_bounds() const
	{
		try
		{
			return { _absolute_bounds.width.value(), _absolute_bounds.height.value() };
		} 
		catch (const std::bad_optional_access&)
		{
			throw std::runtime_error("Bounds not set before rendering. Call 'update_bounds' or 'config()' before rendering");
		}
	}
}
