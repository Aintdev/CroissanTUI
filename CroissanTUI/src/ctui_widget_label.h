#pragma once
#include <cassert>

#include "ctui_kwargs.h"
#include "ctui_msg.h"
#include "ctui_widget.h"
#include "ctui_container.h"
#include "ctui_mod_enum.h"

namespace ctui
{
	struct Label : Widget
	{
		std::string _text = "";
		Color _bg_color = Color::BLACK;
		Color _fg_color = Color::WHITE;
		Align _halign = Align::Center;

		template<typename... Args>
		Label(Container* parent, Args&&... args)
		{
			assert(parent && _CTUIMSG_VSTACK_NO_PARENT);
			if (!parent) throw std::invalid_argument(_CTUIMSG_VSTACK_NO_PARENT);
			parent->make_child(this);
			(apply(std::forward<Args>(args)), ...);
		}

		bool input(Key key) override;
		void render() override;
		void resolve_bounds(int startx, int starty) override;
		void measure() override; // TODO: Implement this and resolve_bounds fix
	private:
		void apply(KWARG_T(text, std::string)	arg)
		{
			_text = arg.value;
			_relative_bounds.width = static_cast<int>(_text.length());
			_relative_bounds.height = 1;
			_relative_bounds.x = _relative_bounds.x.value_or(0);
			_relative_bounds.y = 0;
		}
		void apply(KWARG_T(halign, Align) arg) { _halign = arg.value;  }

		
	protected:
		template<typename T>
		void apply(T&&) {
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}
	};
}
