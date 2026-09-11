#pragma once
#include <memory>
#include <stdexcept>

#include "Widgets/ctui_widget.h"

namespace ctui
{
	template<typename T>
	class WidgetHandler
	{
		T* _widget;
		std::shared_ptr<bool> _alive;

		WidgetHandler(T* widget, std::shared_ptr<bool> alive)
			: _widget(widget),
			_alive(std::move(alive))
		{
			static_assert(std::is_base_of_v<Widget, std::decay<T>>,
				"Object needs to be a Widget.");
		}

	public:
		T& get()
		{
			if (!*_alive)
			{
				throw std::runtime_error("Widget is no longer alive");
			}

			return *_widget;
		}

		operator Widget& ()
		{
			return get();
		}
	};
}
