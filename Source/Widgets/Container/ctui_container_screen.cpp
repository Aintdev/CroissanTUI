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
}
