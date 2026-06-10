#pragma once
#include "ctui_rect.h"
#include "ctui_key.h"

namespace ctui {
	struct Container;

	struct Widget {
	protected:
		Widget() : _parent(nullptr), _relative_bounds(std::nullopt, std::nullopt), _absolute_bounds(std::nullopt, std::nullopt) {}
	public:
		Container*	_parent;
		Rect		_relative_bounds;
		Rect		_absolute_bounds;

		virtual void render() = 0;
		virtual bool input(Key key) = 0;
		virtual void resolve_bounds(int startx, int starty) = 0;
		virtual void measure() = 0;
		virtual ~Widget();
	};
}