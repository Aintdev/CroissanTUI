#include "pch.h"
#include  "ctui_widget.h"
#include "ctui_container.h"
#include <algorithm>

namespace ctui
{
	Widget::~Widget()
	{
		if (!parent)	return;
		if (const auto it = std::ranges::find(parent->children, this); 
			it != parent->children.end())
		{
			parent->children.erase(it);
		}
	}
}
