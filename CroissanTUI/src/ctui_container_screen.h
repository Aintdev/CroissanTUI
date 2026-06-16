#pragma once
#include <complex>

#include "ctui_container_vstack.h"
#include "ctui_mod_enum.h"
#include "ctui_config.h"

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
            auto scr_sz = get_win_size();
            _relative_bounds = Rect(0, 0, scr_sz.first, scr_sz.second);
            _absolute_bounds = _relative_bounds;
            return *this;
        }

        Screen(const Screen&) = delete;
        Screen& operator=(const Screen&) = delete;

        [[deprecated("Do not use screen.render(); Use root_container.render() instead.")]]
        void render() override { VStack::render(); }

        void update_bounds();

    private:
        ctui::Color _background = ctui::Color::BLACK;
        ctui::Color _foreground = ctui::Color::WHITE; //TODO: impliment this and other settings

        template<typename T>
        void apply(T&&) 
		{
            static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
        }

        Screen();
    };
    inline Screen& screen = Screen::instance();
}
