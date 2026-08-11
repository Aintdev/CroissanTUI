#pragma once
#include "Widgets/ctui_widget.h"
#include <vector>

#include "ctui_defaults.h"

namespace ctui {
	struct Container : Widget, protected defaults::WidgetDefaults {
		size_t _focus_index = kFocusIndex;
		std::vector<Widget*> _children = {};
		
		void make_child(Widget* child);
		void remove(Widget* child);

		void render() override;
		~Container() override;
	};
}
