#pragma once

#include <climits>

#include "ctui_rect.h"
#include "ctui_key.h"

namespace ctui {

    struct Container;

    /**
     * Abstract base class for all UI components.
     *
     * Widget provides the basic interface and properties required for
     * measuring, positioning, rendering, and handling user input.
     */
    struct Widget {
    protected:
        Widget()
            : _parent(nullptr),
            _relative_bounds(std::nullopt, std::nullopt),
            _absolute_bounds(std::nullopt, std::nullopt) {
        }

    public:
        Container* _parent;
        Rect _relative_bounds;
        Rect _absolute_bounds;

        /**
         * Handles user input.
         *
         * @param key The key representing the user input.
         * @return `true` if the input was handled, otherwise `false`.
         */
        virtual bool input(Key key) = 0;

        /**
         * Calculates the desired dimensions of the widget based on the
         * available width and the dimensions of its child widgets.
         *
         * @param available_width The maximum width available to the widget.
         * Defaults to `INT_MAX` if no limit is specified.
         */
        virtual void measure(int available_width = INT_MAX) = 0;

        /**
         * Calculates the absolute bounds of the widget.
         *
         * @param startx The x-coordinate of the anchor point.
         * @param starty The y-coordinate of the anchor point.
         */
        virtual void resolve_bounds(int startx, int starty) = 0;

        /**
         * Renders the widget and its child widgets.
         */
        virtual void render() = 0;

        virtual ~Widget();
    };

}
