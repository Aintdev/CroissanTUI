#include "pch.h"
#include "ctui_widget_label.h"

#include "ctui_print.h"

namespace ctui
{
	bool Label::input(Key key)
	{
		return false;
	}

	void Label::layout(int x, int y)
	{
		_actual_bounds = Rect(
			(_desired_bounds.x.value() + x),
			(_desired_bounds.y.value() + y),
			_desired_bounds.width.value(),
			_desired_bounds.height.value()
		);

	}
	
	void Label::render()
	{
		try
		{
			print << Mod::mv_cur(_actual_bounds.x.value(), _actual_bounds.y.value()) << _text;
		} catch (const std::bad_optional_access&)
		{
			throw std::runtime_error("Tried rendering before this->layout() was called.");
		}
	}
}
