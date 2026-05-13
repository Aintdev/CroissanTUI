#pragma once
#include "ctui_widget.h"
#include <vector>

namespace ctui {
	struct Container : Widget {
		int _focus_index = 0;
		std::vector<Widget*> _children = {};
		
		void make_child(Widget* child);
		void remove(Widget* child);

		void render() override;
		~Container() override;
	};
}