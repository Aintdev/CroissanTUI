#include "pch.h"
#include "ctui_widget_label.h"

#include "ctui_print.h"

namespace ctui
{
	bool Label::input(Key key)
	{
		return false;
	}

	void Label::resolve_bounds(int startx, int starty)
	{
		_absolute_bounds = Rect(
			(_relative_bounds.x.value() + startx),
			(_relative_bounds.y.value() + starty),
			_relative_bounds.width.value(),
			_relative_bounds.height.value()
		);
	}
	
	void Label::render()
	{
		try
		{
			print << Mod::mv_cur(_absolute_bounds.x.value(), _absolute_bounds.y.value()) << _text;
		} 
		catch (const std::bad_optional_access&)
		{
			throw std::runtime_error("Tried rendering before this->resolve_bounds() was called.");
		}
	}
}
