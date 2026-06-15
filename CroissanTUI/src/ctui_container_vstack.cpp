#include "pch.h"
#include "ctui_container_vstack.h"
#include <algorithm>

namespace ctui
{
	bool VStack::arrow_handler(const Key key)
	{
		assert((key.type == Key::Type::ArrowDown || key.type == Key::Type::ArrowUp) && "Key must be valid _focus_index changer like ArrowUp oder ArrowDown");
		assert(!_children.empty() && "Stack must have children to change _focus_index. Please check before calling arrow_handler()");

		const int tmp = _focus_index + (key.type == Key::Type::ArrowDown ? 1 : -1);
		_focus_index = std::clamp(tmp, 0, static_cast<int>(_children.size()) - 1);
		return tmp == _focus_index;
	}

	bool VStack::input(const Key key)
	{
		if (_children.empty()) return false;
		if (auto* container = dynamic_cast<Container*>(_children[_focus_index]))
		{
			if (container->input(key)) return true;
		}
		if (key.type == Key::Type::ArrowUp || key.type == Key::Type::ArrowDown)
		{
			return arrow_handler(key);
		}
		return false;
	}

	void VStack::measure()
	{
		int width = 0;
		int curY = 0;

		for (Widget* child : _children)
		{
			child->measure();
			assert(child->_relative_bounds.height.has_value() && "CHILD DOES NOT HAVE HEIGHT");
			curY += child->_relative_bounds.height.value_or(0) + _pady;

			width = std::max(child->_relative_bounds.width.value_or(0), width);
		} 
		curY -= !_children.empty() ? _pady : 0;
		
		_relative_bounds = Rect(width, curY);
	}

	void VStack::resolve_bounds(int startx, int starty)
	{
		assert(_relative_bounds.has_size_values() && "measure() has not been called before resolve_bounds(). Cannot proceed.");

		int curY = starty;

		for (Widget* child : _children)
		{
			int curX = startx;
			if (_halign == Align::Center)
			{
				int rad = child->_relative_bounds.width.value() / 2;
				curX += (_parent->_relative_bounds.width.value() / 2) - rad;				
			} //TODO: Impliment Align::End support
			child->resolve_bounds(curX, curY);

			curY += child->_relative_bounds.height.value() + _pady;
		}

		_absolute_bounds = Rect(startx, starty, _relative_bounds.width.value(), _relative_bounds.height.value());
	}
}
