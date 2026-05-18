#pragma once
#include <complex>
#include <cassert>

#include "ctui_container.h"
#include "ctui_kwargs.h"
#include "ctui_rect.h"
#include "ctui_msg.h"

namespace ctui
{
	struct VStack : Container
	{
		int _pady = 0;

		template<typename... Args>
		VStack(Container* parent, Args&&... args)
		{
			assert(parent && _CTUIMSG_VSTACK_NO_PARENT);
			if (!parent) throw std::invalid_argument(_CTUIMSG_VSTACK_NO_PARENT);
			parent->make_child(this);
			(apply(std::forward<Args>(args)), ...);
		}

	private:
		void apply(KWARG_T(box,			Rect)	arg) { _desired_bounds		=	arg.value; }
		void apply(KWARG_T(pady,		int)	arg) { _pady		=	arg.value; }
		void apply(KWARG_T(focus_index,	int)	arg) { _focus_index =	arg.value; }

		template<typename T>
		void apply(T&&) {
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}
		
		void input(Key key) override;
		void arrow_handler(Key key);
		void layout() override;
	};
}