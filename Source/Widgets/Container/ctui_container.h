#pragma once

#include <vector>

#include "ctui_defaults.h"
#include "Widgets/ctui_widget.h"


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
		
		[[nodiscard]] const std::vector<Widget*>& get_children() const;

		/**
		 * Creates a Widget from type T and gives this ownership.
		 * @tparam T Type of Widget.
		 * @param args Argument passed to T constructor.
		 * @return Reference to constructed widget.
		 */
		template<typename T, typename... Args>
		T& make_child(Args&&... args)
		{
			static_assert(std::is_base_of_v<Widget, T>, "T must derive from Widget");
			auto child = std::make_unique<std::decay_t<T>>(std::forward<Args>(args)...);
			T& ref = *child;
			_children.emplace_back(std::move(child));
			return ref;
		}

		/**
		 * Makes Container owner of given Widget
		 * @tparam T Type of Widget.
		 * @param child Unique pointer to child that Container can add.
		 * @return Reference to constructed widget.
		 */
		template<typename T>
		T& add(std::unique_ptr<T> child)
		{
			static_assert(std::is_base_of_v<Widget, T>, "T must derive from Widget");
			T& ref = *child;
			_children.emplace_back(std::move(child));
			return ref;
		}

		/**
		 * 
		 * @param child 
		 */
		void remove(Widget& child) {
			auto it = std::find_if(_children.begin(), _children.end(),
				[&](const auto& ptr) { return ptr.get() == &child; });
			if (it != _children.end()) {
				_children.erase(it);
			}
		}
		
		/**
		 * Removes child Widget from Container.
		 * @param child Widget that should be removed of Container.
		 */
		void remove(Widget* child);

		/**
		 * Renders alls children
		 */
		void render() override;

		Container(const Container&) = delete;
		Container& operator=(const Container&) = delete;
		Container(Container&&) = delete;
		Container& operator=(Container&&) = delete;

		~Container() override;
	};
}
