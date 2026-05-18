#include "pch.h"
#include "ctui_container_vstack.h"

#include <algorithm>

namespace ctui
{
	void VStack::arrow_handler(Key key)
	{
		assert(key.type == Key::Type::ArrowDown || key.type == Key::Type::ArrowUp, "Key must be valid _focus_index changer like ArrowUp oder ArrowDown");
		assert(!_children.empty(), "Stack must have children to change _focus_index. Please check before calling arrow_handler()");

		_focus_index += key.type == Key::Type::ArrowDown ? 1 : -1;
		_focus_index = std::clamp(_focus_index, 0, static_cast<int>(_children.size()) - 1);
	}

	void VStack::input(const Key key)
	{
		if (key.type == Key::Type::ArrowUp || key.type == Key::Type::ArrowDown)
		{
			if (_children.empty()) return;
			if (auto* container = dynamic_cast<Container*>(_children[_focus_index]))
			{
				container->input(key);
			} else
			{
				arrow_handler(key);
			}
			return;
		}
	}

	void VStack::layout()
	{
		int curY = 0;

		for (Widget* child : _children)
		{
			child->_actual_bounds.x = 0;
			child->_actual_bounds.y = curY;

			child->_actual_bounds.width = _actual_bounds.width;

			int desiredHeight = child->_desired_bounds.height.value_or(0);

			int remainingHeight =
				_actual_bounds.height.value_or(0) - curY;

			int actualHeight = std::min(desiredHeight, remainingHeight);

			if (actualHeight <= 0)
				continue;

			child->_actual_bounds.height = actualHeight;
			child->layout();

			curY += actualHeight;
		}
	}
}
