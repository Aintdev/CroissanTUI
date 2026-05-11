#pragma once
#include "ctui_rect.h"
#include "ctui_key.h"

namespace ctui {
	struct Widget {
		Container* parent;
		Rect bounds;

		virtual void render() = 0;
		virtual void input(Key key) = 0; // handles inputs per widget
		virtual ~Widget();
	};
}