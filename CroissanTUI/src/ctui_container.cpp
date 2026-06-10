#include "pch.h"
#include "ctui_container.h"

namespace ctui
{
	void Container::render()
	{
		resolve_bounds(0, 0);
		for (Widget* child : _children)
		{
			child->render();
		}
	}

	void Container::remove(Widget* child)
	{
		if (const auto it = std::ranges::find(_children, child);
			it != _children.end())
		{
			_children.erase(it);
		}
	}

	void Container::make_child(Widget* child)
	{
		child->_parent = this;
		_children.emplace_back(child);
	}

	Container::~Container()
	{
		while (!_children.empty())
			delete _children.back();

		if (_parent)
			_parent->remove(this);
	}
}
