#pragma once
#include <unordered_map>

namespace ctui {
	struct Key {
        enum class Type {
			Unknown,

			Character,
			Ctrl,

			Tab,
			Backspace,
			Enter,
			Escape,

			ArrowUp,
			ArrowDown,
			ArrowLeft,
			ArrowRight,

			DeleteKey,
			Insert,

			Home,
			End,

			PageUp,
			PageDown,

			F1, F2, F3, F4,
			F5, F6, F7, F8,
			F9, F10, F11, F12
		};
#ifndef _WIN32
        static const std::unordered_map<std::string, Type> sequences;
#endif
        Type type;
        char ch;
    };

    Key readKey();  // liest einen Tastendruck und gibt Key zurück
}