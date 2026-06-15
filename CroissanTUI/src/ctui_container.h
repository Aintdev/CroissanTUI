#pragma once
#include "ctui_widget.h"
#include <vector>

#include "ctui_defaults.h"

namespace ctui {
	struct Container : Widget {
		int _focus_index = defaults::FOCUS_INDEX;
		std::vector<Widget*> _children = {};
		
		void make_child(Widget* child);
		void remove(Widget* child);

		void render() override;
		~Container() override;
	};
}
