#include "pch.h"
#include "ctui_widget_label.h"

#include "ctui_print.h"

namespace ctui
{
	bool Label::input(Key key)
	{
		return false;
	}

	void Label::measure()
	{
		_relative_bounds = Rect(static_cast<int>(_text.length()), 1); //  TODO: THIS IS A TEMP FIX AND SHOULD NOT BE USED IN FINAL
	}																					// TODO: CAUSE MULTIPLE LINES DO NOT WORK OR ANY OTHER STUFF :O

	void Label::resolve_bounds(int startx, int starty)
	{
		_absolute_bounds = Rect(
			(_relative_bounds.x.value_or(0) + startx),
			(_relative_bounds.y.value_or(0) + starty),
			_relative_bounds.width.value(),
			_relative_bounds.height.value()
		); //TODO: fix cause its way oversimplified and needs more edge case 
	}
	
	void Label::render()
	{
		try //TODO: Impliment Multiline functionality and other stuff ykwim
		{
			print << Mod::mv_cur(_absolute_bounds.x.value(), _absolute_bounds.y.value()) << _text;
		} 
		catch (const std::bad_optional_access&)
		{
			throw std::runtime_error("Tried rendering before this->resolve_bounds() was called.");
		}
	}
}
