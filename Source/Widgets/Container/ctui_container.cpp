#include "pch.h"
#include "ctui_container.h"

namespace ctui
{
	void Container::render()
	{
		for (std::unique_ptr<Widget>& child : _children)
		{
			child->render();
		}
	}

	void Container::remove(Widget& child)
	{
		auto it = std::ranges::find_if(_children,
			[&](const auto& ptr) {
				return ptr.get() == &child;
			});

		if (it != _children.end())
			_children.erase(it);
	}

	int Container::get_focus_index() const
	{
		return _focus_index;
	}

	const std::vector<std::unique_ptr<Widget>>& Container::get_children() const
	{
		return _children;
	}

	Container::~Container()
	{
		while (!_children.empty())
			remove(*_children.back());
	}
}
