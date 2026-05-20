#include "pch.h"

#include "ctui_container_screen.h"
#include "ctui_config.h"

namespace ctui
{
	Screen::Screen() : VStack()
	{
		const auto [fst, snd] = get_win_size();
		_desired_bounds = Rect(0, 0, fst, snd);
		_actual_bounds = _desired_bounds;
	}


}