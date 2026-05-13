#include "pch.h"
#include  "ctui_widget.h"
#include "ctui_container.h"

namespace ctui
{
	Widget::~Widget()
	{
		if (!_parent)	return;
		_parent->remove(this);
	}
}
