#include "pch.h"
#include "ctui_container.h"

#include <windows.h>

namespace ctui
{
	void Container::render()
	{
		for (Widget* child : children)
		{
			child->render();
		}
	}

	void Container::remove(Widget* child)
	{
		if (const auto it = std::ranges::find(children, child);
			it != children.end())
		{
			children.erase(it);
		}
	}

	void Container::makeChild(Widget* child)
	{
		child->parent = this;
		children.emplace_back(child);
	}

	Container::~Container()
	{
		while (!children.empty())
			delete children.back();

		if (parent)
			parent->remove(this);
	}
}
