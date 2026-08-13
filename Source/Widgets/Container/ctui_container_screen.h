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
            VStack::config(std::forward<Args>(args)...);
            update_bounds();
            return *this;
        }

        Screen(const Screen&) = delete;
        Screen& operator=(const Screen&) = delete;

        [[deprecated("Do not use screen.render(); Use root_container.render() instead.")]]
        void render() override { VStack::render(); }

        void update_bounds();
        std::pair<int, int> get_bounds() const;

    private:
        template<typename T>
        void apply(T&&) 
		{
            static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
        }

        Screen();
    };
    inline Screen& screen = Screen::instance();
}
