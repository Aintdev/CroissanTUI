#pragma once
#include "ctui_widget.h"
#include <vector>

namespace ctui {
	struct Container : Widget {
		std::vector<Widget*> children;
		
		void add(Widget* child);
		void remove(Widget* child);

		void render() override;
		virtual void input(Key key) override;
		~Container() override;
	};
}