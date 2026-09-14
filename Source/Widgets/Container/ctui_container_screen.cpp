#include "pch.h"

#include "ctui_container_screen.h"
#include "ctui_config.h"
#include "ctui_raw_mode.h"

namespace ctui
{
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

	void Screen::run(const std::function<void(RunStage)>& stage_callback)
	{
		RawModeGuard rwg;
		
		auto win_size = get_win_size();
		bool resized = false;

		running = true;
		while (running)
		{
			auto new_winsize = get_win_size();
			if (new_winsize != win_size)
			{
				win_size = new_winsize;
				this->update_bounds(); // update screen width and height
				std::cout << "\033[?2026h" << "\033[2J\033[H"; // DEC Private Mode Set & Clear Screen
				resized = true;
			}

			this->measure(win_size.first); // measure all widgets

			this->resolve_bounds(0, 0);  // add the positions together to let the widgets know their absolute positions

			this->render(); // print to screen
			if (resized)
			{
				resized = false;
				std::cout << "\033[?2026l";
			}
		}
	}
}
