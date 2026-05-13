#include "pch.h"
#include "ctui_container_vstack.h"

namespace ctui
{
	void VStack::input(Key key)
	{
		return;
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
