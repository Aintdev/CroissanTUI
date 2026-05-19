#pragma once
#include <string>
#include "ctui_mod_enum.h"

namespace ctui {
	struct Mod {
		
		Mod(GraphicMod m);
		Mod(const char(&s)[3], Color c);

		static Mod mvCur(int x, int y);
		static Mod clearPath(int x_begin, int line, int x_end);

		operator const std::string() const;
	private:
		std::string code;
		Mod(int x, int y);
		Mod(std::string x);
	};
}