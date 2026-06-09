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

	void VStack::layout(int x, int y)
	{
		if (!_parent) return; // if VSTACK is Screen
		_actual_bounds = Rect(
			_parent->_actual_bounds.x.value(),
			_parent->_actual_bounds.y.value(),
			_parent->_actual_bounds.width.value(),
			_parent->_actual_bounds.height.value()
		);
		for (auto* child : _children)
		{
			int x_extra = 0;
			if (_align == Align::Center)
				x_extra += (_actual_bounds.width.value() / 2) - (child->_desired_bounds.width.value() / 2);
			else if (_align == Align::End)
				x_extra += _actual_bounds.width.value() - child->_desired_bounds.width.value() + 1;
			child->layout(x + x_extra, y);
			y += child->_actual_bounds.height.value();
			y += _pady;
		}
	}
}
