#pragma once
#include "ctui_mod.h"
#include <iostream>

namespace ctui {
    struct Stream {
        template<typename T>
        Stream& operator<<(const T& val) {
            if constexpr (std::is_constructible_v<Mod, T>) {
                std::cout << static_cast<std::string>(Mod(val));
            }
            else {
                std::cout << val;
            }
            return *this;
        }
    };
    static Stream print;
}