#pragma once
#include <cassert>
#include <climits>
#include <stdexcept>

#include "ctui_container.h"
#include "ctui_kwargs.h"
#include "ctui_mod_enum.h"
#include "ctui_msg.h"
#include "ctui_defaults.h"

namespace ctui
{
	/**
	 * @class VStack
	 * @brief A container that stacks its children vertically.
	 *
	 * @details
	 * VStack renders its child widgets top to bottom, distributing available
	 * height according to each child's measure() result. Children are laid
	 * out in insertion order; spacing between them can be controlled via
	 * the `pady` KWARG.
	 *
	 * @par KWARGs
	 * | KWARG        | Type    | Description                                            |
	 * |--------------|---------|--------------------------------------------------------|
	 * | `pady`       | `int`   | Vertical gap in rows between consecutive children.     |
	 * | `focus`      | `int`   | Sets the starting focus index.                         |
	 * | `fill`       | `bool`  | Whether the stack expands to fill the available space. |
	 * | `halign`     | `Align` | Where to align widgets horizontally in the container.  |
	 *
	 * Example:
	 * @code
	 * WidgetHandler<VStack> stack = parent->make_child<VStack>(
	 *     pady = 2,
	 *     fill = true
	 * );
	 * stack->make_child<Label>(text = "Hello");
	 * @endcode
	 *
	 * @see Widget
	 * @see Container
	 */
	class VStack : public Container
	{
	protected:
		/**
		 * Padding between the directly owned children.
		 *
		 * Meaning the first child has 0 padding and the last doesn't leave any space below it.
		 */
		int _pady = kPady;
		/// Horizontal alignment of the children within the container.
		Align _halign = kHalign;
		/// Makes the container fill the entire available space given to it.
		bool _fill = kFill;

		VStack() = default;
	public:
		/**
		 * @brief Applies one or more KWARGs to reconfigure this VStack.
		 *
		 * Example usage:
		 * @code
		 * stack.config(pady = 3, halign = Align::End);
		 * @endcode
		 * @tparam Args Deduced KWARG assignment types.
		 * @param args Any KWARGs supported by VStack (see class documentation).
		 * @return Reference to *this, to allow chaining further calls.
		 */
		template<typename... Args>
		VStack& config(Args&&... args)
		{
			(apply(std::forward<Args>(args)), ...);
			return *this;
		}

		/**
		 * @brief Constructs a VStack as a child of the given parent and applies the KWARGs.
		 *
		 * Example usage:
		 * @code
		 * VStack stack(parent, pady = 3, halign = Align::End);
		 * @endcode
		 * @tparam Args Deduced KWARG assignment types.
		 * @param parent The container that owns this stack. Must not be `nullptr`.
		 * @param args Any KWARGs supported by VStack (see class documentation).
		 * @throws std::invalid_argument If `parent` is `nullptr`.
		 */
		template<typename... Args>
		VStack(Container* parent, Args&&... args)
		{
			assert(parent && _CTUIMSG_VSTACK_NO_PARENT);
			if (!parent) throw std::invalid_argument(_CTUIMSG_VSTACK_NO_PARENT);
			set_parent(parent);
			config(std::forward<Args>(args)...);
		}

		// TODO: Getters :)

		/**
		 * @brief Moves the focus index of the stack up or down by one child, or passes the call down to the focused Container.
		 *
		 * Input is processed in this order:
		 *  1. If the stack has no children, the key is not handled.
		 *  2. If the currently focused child is a `Container`, the key is forwarded
		 *     to it. If the child consumes the key, handling stops here.
		 *  3. Otherwise, ArrowUp / ArrowDown move the focus between children via
		 *     `arrow_handler()`.
		 *  4. Any other key is not handled.
		 *
		 * This lets nested containers (e.g. a stack inside a stack) use the arrow keys
		 * for their own focus first. Only when the inner container is at its edge
		 * (and therefore returns `false`) does the outer stack move its focus.
		 *
		 * @param key The key event to process.
		 *
		 * @return `true` if the key was consumed (by the focused child or by a
		 *         successful focus change), `false` if it was not handled and should
		 *         be passed on to the parent.
		 *
		 * @note Implementation incomplete: Focused children that are not a
		 *       `Container` do not receive the key.
		 * @note At the first/last child, ArrowUp/ArrowDown return `false`, because
		 *       `arrow_handler()` reports no change. The key therefore bubbles up.
		 */
		bool input(Key key) override;

		/**
		 * @brief Calculates the desired dimensions of the stack.
		 *
		 * The size is derived from the available width and the dimensions
		 * of the child widgets, including the `pady` spacing between them.
		 *
		 * @param available_width The maximum width available to the widget.
		 * Defaults to `INT_MAX` if no limit is specified, which lets the widget
		 * size itself up.
		 */
		void measure(int available_width = INT_MAX) override;

		/**
		 * @brief Calculates the absolute bounds of the stack and its children.
		 *
		 * Should be called after measure().
		 *
		 * @param startx The x-coordinate of the anchor point.
		 * @param starty The y-coordinate of the anchor point.
		 */
		void resolve_bounds(int startx, int starty) override;

	private:
		void apply(KWARG_T(pady, int)	arg) { _pady = arg.value; }
		void apply(KWARG_T(focus, int)	arg) { _focus_index = arg.value; }
		void apply(KWARG_T(halign, Align)	arg) { _halign = arg.value; }
		void apply(KWARG_T(fill, bool)	arg) { _fill = arg.value; }

	protected:
		template<typename T>
		void apply(T&&)
		{
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}

		/**
		 * @brief Moves the focus index of the stack up or down by one child.
		 *
		 * ArrowDown increments `_focus_index`, ArrowUp decrements it. The result is
		 * clamped to the valid range `[0, _children.size() - 1]`, so focus does not
		 * wrap around at either end.
		 *
		 * @param key The key event that triggered the move. Must be of type
		 *            `Key::Type::ArrowDown` or `Key::Type::ArrowUp`.
		 *
		 * @return `true` if the focus index actually changed, `false` if it was
		 *         already at the first/last child and the move was clamped.
		 *
		 * @pre `key.type` is `ArrowDown` or `ArrowUp`.
		 * @pre The stack has at least one child. Callers must check this
		 *      before calling.
		 *
		 * @note Both preconditions are only checked via `assert`, so they are not
		 *       enforced in release builds (`NDEBUG`).
		 * @note This only updates the index. It does not redraw or change the
		 *       focus state of the children.
		 */
		bool arrow_handler(Key key);
	};
}