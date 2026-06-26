#pragma once
#include <cassert>

#include "ctui_kwargs.h"
#include "ctui_msg.h"
#include "ctui_widget.h"
#include "ctui_container.h"
#include "ctui_mod_enum.h"
#include "ctui_text.h"

namespace ctui
{
	struct Label : Widget
	{
		std::vector<std::string> _lines = { defaults::kText };
		Color _bg_color = defaults::kBgColor;
		Color _fg_color = defaults::kFgColor;
		Align _halign = defaults::kHalign;
		bool _fill = defaults::kFill;

		template<typename... Args>
		Label& config(Args&&... args)
		{
			(apply(std::forward<Args>(args)), ...);
			return *this;
		}

		template<typename... Args>
		Label(Container* parent, Args&&... args)
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
		void render() override;

	private:
		void apply(KWARG_T(text,	std::string) arg)
		{
			_lines = str_to_lines(arg.value);
			for (auto& line : _lines)
				if (!line.empty() && line.back() == '\r')
					line.pop_back();
		}
		void apply(KWARG_T(fill, bool) arg) { _fill = arg.value; }

	protected:
		template<typename T>
		void apply(T&&)
		{
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}
	};
}
