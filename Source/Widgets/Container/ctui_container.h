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
