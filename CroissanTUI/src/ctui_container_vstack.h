#pragma once
#include <complex>
#include <cassert>

#include "ctui_container.h"
#include "ctui_kwargs.h"
#include "ctui_mod_enum.h"
#include "ctui_msg.h"
#include "ctui_defaults.h"

namespace ctui
{
	struct VStack : Container
	{
		int _pady = defaults::PADY;
		Align _halign = defaults::HALIGN;

	protected:
		VStack() = default;
	public:

		template<typename... Args>
		VStack& config(Args&&... args)
		{
			(apply(std::forward<Args>(args)), ...);
			return *this;
		}

		template<typename... Args>
		VStack(Container* parent, Args&&... args)
		{
			assert(parent && _CTUIMSG_VSTACK_NO_PARENT);
			if (!parent) throw std::invalid_argument(_CTUIMSG_VSTACK_NO_PARENT);
			parent->make_child(this);
			config(args...);
		}

		bool input(Key key) override;

		// getters

		// TODO: Getters :)

		void resolve_bounds(int startx, int starty) override;
		void measure() override;

	protected:
		void apply(KWARG_T(pady,		int)	arg) { _pady		=	arg.value; }
		void apply(KWARG_T(focus_index,	int)	arg) { _focus_index	=	arg.value; }
		void apply(KWARG_T(halign,		Align)	arg) { _halign		=	arg.value; }
		template<typename T>
		void apply(T&&) {
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}
		bool arrow_handler(Key key);
		
	};
}
