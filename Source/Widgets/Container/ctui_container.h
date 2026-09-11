#pragma once

#include <vector>

#include "ctui_defaults.h"
#include "Widgets/ctui_widget.h"
#include "ctui_widget_handler.h"


namespace ctui {
	/**
	 * Abstract base class for all Container components.
	 *
	 * Container provides basic functionality to add and remove Widgets.
	 */
	struct Container : Widget, protected defaults::WidgetDefaults {
	protected:
		/// Index of Container::_children where focus is set to.
		int _focus_index = kFocusIndex;

		/// Children that the Container is the parent of
		std::vector<std::unique_ptr<Widget>> _children = {};

		Container() = default;
	public:
		// Getters
		[[nodiscard]] int get_focus_index() const;

		[[nodiscard]] const std::vector<std::unique_ptr<Widget>>& get_children() const;

		/**
		 * Creates a Widget from type T and gives this ownership.
		 * @tparam T Type of Widget.
		 * @param args Argument passed to T constructor.
		 * @return Reference to constructed widget.
		 */
		template<typename T, typename... Args>
		WidgetHandler<T> make_child(Args&&... args)
		{
			static_assert(std::is_base_of_v<Widget, T>, "T must derive from Widget");
			auto child = std::make_unique<std::decay_t<T>>(this, std::forward<Args>(args)...);
			return WidgetHandler<T>(static_cast<T*>(_children.emplace_back(std::move(child)).get()));
		}

		/**
		 * Removes widget from a child from Container. Does nothing if child is not from this Container.
		 * @param child Widget to remove
		 */
		void remove(Widget& child);

		/**
		 * Renders alls children
		 */
		void render() override;

		~Container() override;
	};
}
