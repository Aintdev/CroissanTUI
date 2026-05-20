#pragma once
#include <cassert>

#include "ctui_kwargs.h"
#include "ctui_msg.h"
#include "ctui_widget.h"
#include "ctui_container.h"

namespace ctui
{
	struct Label : Widget
	{
		std::string text = "";

		template<typename... Args>
		Label(Container* parent, Args&&... args)
		{
			assert(parent && _CTUIMSG_VSTACK_NO_PARENT);
			if (!parent) throw std::invalid_argument(_CTUIMSG_VSTACK_NO_PARENT);
			parent->make_child(this);
			(apply(std::forward<Args>(args)), ...);
		}

		bool input(Key key) override;
	private:
		void apply(KWARG_T(box, Rect)			arg) { _desired_bounds = arg.value; }
		void apply(KWARG_T(text, std::string)	arg) { text = arg.value; }
	protected:
		template<typename T>
		void apply(T&&) {
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}
	};
}
