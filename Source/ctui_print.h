#pragma once

#include "ctui_mod_enum.h"
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

namespace ctui {
    /**
     * @struct PrintStream
     * @brief Buffered output stream with ANSI support for `Color` and `GraphicMod`.
     *
     * Values are collected via `operator<<` and only written to `std::cout`
     * when `exec()` is called.
     *
     * @code
     * print << Color::Red << "Hello" << GraphicMod::Reset << "\n";
     * print.exec();
     * @endcode
     */
    struct PrintStream {
        /**
         * @brief Appends a value to the buffer.
         *
         * `Color` and `GraphicMod` are converted to ANSI escape sequences,
         * everything else is streamed unchanged.
         *
         * @param val The value to append.
         * @return Reference to *this, to allow chaining.
         */
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

        /// @brief Writes the buffer to `std::cout` and clears it.
        void exec()
        {
            std::cout << _ss.str();
            _ss.str("");
            _ss.clear();
        }

    private:
        std::ostringstream _ss; ///< Buffer until exec() is called.
    };

    /// Global PrintStream instance.
    static PrintStream print;
}
