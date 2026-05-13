#pragma once
#include "ctui_rect.h"
#include "ctui_key.h"

namespace ctui {
	struct Container;

	struct Widget {
	protected:
		Widget() : _parent(nullptr), _desired_bounds(std::nullopt, std::nullopt), _actual_bounds(std::nullopt, std::nullopt) {}
	public:
		Container*	_parent;
		Rect		_desired_bounds;
		Rect		_actual_bounds;

		virtual void render() = 0;
		virtual void input(Key key) = 0;
		virtual void layout() = 0;
		virtual ~Widget();
	};
}