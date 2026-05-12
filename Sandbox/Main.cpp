#include "ctui.h"
#include <chrono>
#include <thread>
#include <cstdio>

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;
using namespace ctui;

static void foo(const KWARG_T(width, int) arg) {
	std::cout << arg.value;
}

KWARG(width_percent);

static void bar(const KWARG_T(width_percent, Percent) arg) {
	std::cout << arg.value.toPixels(200);
}

int main() {
	foo(width=25);
	bar(width_percent = 20_pct);

	enableRawMode();
	while (true) {
		print << getCursorPos().col << " " << getCursorPos().row << "\n-> ";
		Key a = readKey();
		//print << a.ch << " " << (int)a.type << "\n";
	}
	

	//print << Mod::mvCur(20, 12) << GRAPHIC_MOD::ITALIC << color::FG::BLUE << color::BG::WHITE << "Test" << GRAPHIC_MOD::RESET_ALL << Mod::mvCur(0, 30);
	//sleep_for(2s);
	//print << Mod::mvCur(20, 12) << GRAPHIC_MOD::ITALIC << color::FG::RED << color::BG::WHITE << "Im Blue dabidi dabidai" << GRAPHIC_MOD::RESET_ALL << Mod::mvCur(0, 30);
	//sleep_for(2s);
	//print << Mod::clearPath(20, 12, 60);
	disableRawMode();
}