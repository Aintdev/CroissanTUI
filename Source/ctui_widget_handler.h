#pragma once
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace ctui
{
	struct Widget;
	struct Container;
	struct Screen;

	/**
	 * Handler to control a Widget safely that safely handles unsafe access.
	 * @tparam T Type of the Widget it handles.
	 */
	template<typename T>
	class WidgetHandler
	{
		T* _widget;
		std::shared_ptr<bool> _alive;

		friend struct Container;
		friend struct Screen;

		WidgetHandler(T* widget)
			: _widget(widget)
		{
			static_assert(std::is_base_of_v<Widget, std::decay_t<T>>,
				"Object needs to be a Widget.");
			if (!_widget)
				throw std::invalid_argument("WidgetHandler cannot wrap a null Widget");
			_alive = _widget->get_alive_ptr();
		}

	public:
		/**
		 * Gets Widget if it's still alive.
		 * @return Reference to Widget.
		 * @throws std::runtime_error if Widget is no longer alive.
		 */
		T& get()
		{
			if (!*_alive)
			{
				throw std::runtime_error("Widget is no longer alive");
			}

			return *_widget;
		}

		/**
		 * Gets Widget if it's still alive.
		 * @return Reference to Widget.
		 * @throws std::runtime_error if Widget is no longer alive.
		 */
		operator Widget& ()
		{
			return get();
		}

		/**
		 * Gets Widget if it's still alive.
		 * @return Reference to Widget.
		 * @throws std::runtime_error if Widget is no longer alive.
		 */
		T* operator->()
		{
			return &get();
		}
	};
}
