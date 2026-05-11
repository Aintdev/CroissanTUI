#include "pch.h"
#include "ctui_key.h"
#ifdef _WIN32
	#include <conio.h>
#else
	#include <unistd.h>
#endif

namespace ctui {

	using enum Key::Type;

#ifndef _WIN32
    const std::unordered_map<std::string, Key::Type> Key::sequences = {
        {"\x1b[A", ArrowUp},
        {"\x1b[B", ArrowDown},
        {"\x1b[C", ArrowRight},
        {"\x1b[D", ArrowLeft},

        {"\x1b[3~", DeleteKey},
        {"\x1b[2~", Insert},

        {"\x1b[H", Home},
        {"\x1b[F", End},

        {"\x1b[5~", PageUp},
        {"\x1b[6~", PageDown},

        {"\x1bOP", F1},
        {"\x1bOQ", F2},
        {"\x1bOR", F3},
        {"\x1bOS", F4},

        {"\x1b[15~", F5},
        {"\x1b[17~", F6},
        {"\x1b[18~", F7},
        {"\x1b[19~", F8},

        {"\x1b[20~", F9},
        {"\x1b[21~", F10},
        {"\x1b[23~", F11},
        {"\x1b[24~", F12},
    };
#endif

	Key readKey() {
		
#ifdef _WIN32
		int first = _getch();
		if (first >= 32 && first <= 126)
			return { Character, (char)first };

		if (first == 9)
			return { Tab };

		if (first == 8)
			return { Backspace };

		if (first == 13)
			return { Enter };

		if (first == 27)
			return { Escape };

		if (first >= 1 && first <= 26)
			return { Ctrl, (char)(first + 'A' - 1) };

		if (first == 0 || first == 224) {
			int second = _getch();
			switch (second) {
			case 72:	return { ArrowUp };
			case 75:	return { ArrowLeft };
			case 77:	return { ArrowRight };
			case 80:	return { ArrowDown };
			case 83:	return { DeleteKey };
			case 71:	return { Home };
			case 73:	return { PageUp };
			case 79:	return { End };
			case 81:	return { PageDown };
			case 82:	return { Insert };

			case 59:	return { F1 };
			case 60:	return { F2 };
			case 61:	return { F3 };
			case 62:	return { F4 };
			case 63:	return { F5 };
			case 64:	return { F6 };
			case 65:	return { F7 };
			case 66:	return { F8 };
			case 67:	return { F9 };
			case 68:	return { F10 };
			case 133:	return { F11 };
			case 134:	return { F12 };
			}
		}

		return Key();
#else
		char c;

		if (read(STDIN_FILENO, &c, 1) <= 0)
			return { Unknown };

		if (c >= 32 && c <= 126)
			return { Character, c };

		if(c == 9)
			return { Tab };

		if (c == 10)
			return { Enter };

		if (c >= 1 && c <= 26)
			return { Ctrl, (char)(c + 'A' - 1) };

		if (c == 127)
			return { Backspace };

		if (c != 27)
			return { Unknown };

		std::string seq(1, c);

		for (int i = 0; i < 7; i++) {
			char next;

			if (read(STDIN_FILENO, &next, 1) <= 0)
				break;

			seq += next;

			auto it = Key::sequences.find(seq);

			if (it != Key::sequences.end())
				return { it->second };
		}

		return { Escape };
#endif
	}
}