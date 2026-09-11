#pragma once
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace ctui
{
	class Widget;

	template<typename T>
	class WidgetHandler
	{
		T* _widget;
		std::shared_ptr<bool> _alive;

	public:
		WidgetHandler(T* widget)
			: _widget(widget)
		{
			static_assert(std::is_base_of_v<Widget, std::decay_t<T>>,
				"Object needs to be a Widget.");
			_alive = _widget->get_alive_ptr();
		}

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

		T* operator->()
		{
			return &get();
		}
	};
}
