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
		{
			const auto removed_index = static_cast<int>(it - _children.begin());
			_children.erase(it);
			if (_children.empty())
				_focus_index = -1;
			else
			{
				if (_focus_index > removed_index)
					--_focus_index;
				if (_focus_index >= static_cast<int>(_children.size()))
					_focus_index = static_cast<int>(_children.size()) - 1;
			}
		}
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
