#pragma once

#include "ctui_mod_enum.h"
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace ctui {
    struct PrintStream {
        template<typename T>
        PrintStream& operator<<(const T& val) 
    	{
            if constexpr (std::is_same_v<Color, T>) 
            {
                unsigned int x = static_cast<unsigned int>(val);
                if (x <= 7)
                    x += 30u;
            	_ss << std::string("\033[") + std::to_string(x) + "m";
            } 
        	else if constexpr (std::is_same_v<GraphicMod, T>) 
            {
                unsigned int x = static_cast<unsigned int>(val);
            	_ss << std::string("\033[") + std::to_string(x) + "m";
            }
            else 
            {
                _ss << val;
            }
            return *this;
        }

        void exec()
        {
            std::cout << _ss.str();
            _ss.str("");
            _ss.clear();
        }

    private:
        std::ostringstream _ss;
    };
    static PrintStream print;
}
