#include "ctui.h"
#include <chrono>
#include <thread>
#include <cstdio>

using namespace std::this_thread;
using namespace std::chrono_literals;
using namespace ctui;


int main() {
	VStack main = VStack(&screen, pady=3);
	screen.config(pady = 5);
	enableRawMode();
	

	//print << Mod::mvCur(20, 12) << GRAPHIC_MOD::ITALIC << color::FG::BLUE << color::BG::WHITE << "Test" << GRAPHIC_MOD::RESET_ALL << Mod::mvCur(0, 30);
	//sleep_for(2s);
	//print << Mod::mvCur(20, 12) << GRAPHIC_MOD::ITALIC << color::FG::RED << color::BG::WHITE << "Im Blue dabidi dabidai" << GRAPHIC_MOD::RESET_ALL << Mod::mvCur(0, 30);
	//sleep_for(2s);
	//print << Mod::clearPath(20, 12, 60);
	disableRawMode();
}