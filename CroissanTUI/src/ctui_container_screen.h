#pragma once
#include <complex>

#include "ctui_container_vstack.h"
#include "ctui_mod_enum.h"

namespace ctui
{
    struct Screen : VStack
    {
        static Screen& instance()
        {
            static Screen s_instance;
            return s_instance;
        }

        template<typename... Args>
        Screen& config(Args&&... args)
        {
            (apply(std::forward<Args>(args)), ...);
            return *this;
        }

        Screen(const Screen&) = delete;
        Screen& operator=(const Screen&) = delete;

        // getters
        ctui::Color get_color_bg() const { return _background; }
        ctui::Color get_color_fg() const { return _foreground; }

    private:
        ctui::Color _background = ctui::Color::BLACK;
        ctui::Color _foreground = ctui::Color::WHITE;

        template<typename T>
        void apply(T&&) {
            static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
        }

        Screen();

        void apply(KWARG_T(fg, ctui::Color)	    arg) { _foreground = arg.value; }
        void apply(KWARG_T(bg, ctui::Color)	    arg) { _background = arg.value; }
        void apply(KWARG_T(pady, int)       	arg) { _pady = arg.value; }
    };
    inline Screen& screen = Screen::instance();
}
