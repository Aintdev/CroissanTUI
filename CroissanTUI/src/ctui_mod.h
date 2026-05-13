#pragma once
#include <string>
#include "ctui_mod_enum.h"

namespace ctui {
	struct Mod {
		
		Mod(const GRAPHIC_MOD m);
		Mod(color::FG c);
		Mod(color::BG c);

		static Mod mvCur(int x, int y);
		static Mod clearPath(int x_begin, int line, int x_end);

		operator const std::string() const;
	private:
		std::string code;
		Mod(int x, int y);
		Mod(std::string x);
	};
}