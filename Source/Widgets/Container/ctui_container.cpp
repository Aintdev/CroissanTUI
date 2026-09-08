#include "pch.h"
#include "ctui_container.h"

namespace ctui
{
	void Container::render()
	{
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

	int Container::get_focus_index() const
	{
		return _focus_index;
	}

	const std::vector<Widget*>& Container::get_children() const
	{
		return _children;
	}

	void Container::make_child(Widget* child)
	{
		child->set_parent(this);
		_children.emplace_back(child);
	}

	Container::~Container()
	{
		while (!_children.empty())
			_children.back()->set_parent(nullptr);

		if (_parent)
			_parent->remove(this);
	}
}
