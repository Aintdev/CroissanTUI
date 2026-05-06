#include "pch.h"
#include "ctui_mod.h"

namespace ctui {
	Mod::Mod(GRAPHIC_MOD m) : code("\033[" + std::to_string((int)m) + "m") {};
	Mod::Mod(color::FG c) : code("\033[" + std::to_string((int)c) + "m") {};
	Mod::Mod(color::BG c) : code("\033[" + std::to_string((int)c) + "m") {};
	Mod::Mod(int x, int y) : code("\033[" + std::to_string(y) + ";" + std::to_string(x) + "f") {}
	Mod::Mod(std::string x) : code(x) {}

	const std::string Mod::getCode() const { return code; }

	Mod Mod::mvCur(int x, int y) { return Mod(x, y); }
	Mod Mod::clearPath(int x1, int line, int x2) {
		std::string result = std::string("\x1b""7") + std::string("\033[") + std::to_string(line) + std::string(";") + std::to_string(x1) + std::string("H");
		result += std::string(x2 - x1, ' ') + std::string("\x1b""8");
		return Mod(result);
	}

	Mod::operator const std::string& () const {
		return code;
	}
}