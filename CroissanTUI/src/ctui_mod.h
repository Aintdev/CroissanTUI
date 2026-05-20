#pragma once
#include <string>
#include "ctui_mod_enum.h"

namespace ctui {
	struct Mod {
		
		Mod(GraphicMod m);
		Mod(const char(&s)[3], Color c);

		static Mod mv_cur(int x, int y);
		static Mod clear_path(int x_begin, int line, int x_end);

		operator const std::string() const;
	private:
		std::string _code;
		Mod(int x, int y);
		Mod(std::string x);
	};
}