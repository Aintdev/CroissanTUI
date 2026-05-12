#pragma once
#include "ctui_widget.h"
#include "ctui_kwargs.h"
#include <vector>

namespace ctui {
	struct Container : Widget {
		int focusIndex;
		std::vector<Widget*> children;
		
		void makeChild(Widget* child);
		void remove(Widget* child);

		void render() override;
		virtual void input(Key key) override = 0;
		~Container() override;
	};
}