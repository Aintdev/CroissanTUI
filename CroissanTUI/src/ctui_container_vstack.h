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
		int _pady = defaults::kPady;
		Align _halign = defaults::kHalign;
		bool _fill = defaults::kFill;

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

		// TODO: Getters :)

		bool input(Key key) override;
		void measure(int available_width = INT_MAX) override;
		void resolve_bounds(int startx, int starty) override;

	private:
		void apply(KWARG_T(pady,		int)	arg) { _pady		=	arg.value; }
		void apply(KWARG_T(focus_index,	int)	arg) { _focus_index	=	arg.value; }
		void apply(KWARG_T(halign,		Align)	arg) { _halign		=	arg.value; }
		void apply(KWARG_T(fill,		bool)	arg) { _fill		=	arg.value; }

	protected:
		template<typename T>
		void apply(T&&) 
		{
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}
		bool arrow_handler(Key key);
	};
}
