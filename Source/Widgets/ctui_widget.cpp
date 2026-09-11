#include "pch.h"
#include  "ctui_widget.h"
#include "Container/ctui_container.h"

namespace ctui
{
	const Rect& Widget::get_relative_bounds() const
	{
		return _relative_bounds;
	}

	const Rect& Widget::get_absolute_bounds() const
	{
		return _absolute_bounds;
	}

	const Widget& Widget::get_parent() const
	{
		return *_parent;
	}

	void Widget::set_parent(Container* parent_ptr)
	{
		_parent = parent_ptr;
	}

	Widget::~Widget()
	{
		*_alive = false;
	}
}
