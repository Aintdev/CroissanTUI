#include "ctui.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono_literals;
using std::chrono::system_clock;
using namespace ctui;

int main() {
	enableRawMode();
	
	while (true) {
		std::pair<int, int> size = getWindowSize();
		int xd = size.first;
		int yd = size.second;
		print << xd << ", " << yd << "\n";
		Key a = readKey();
		print << a.ch << " " << (int)a.type << "\n";
	}
	

	//print << Mod::mvCur(20, 12) << GRAPHIC_MOD::ITALIC << color::FG::BLUE << color::BG::WHITE << "Test" << GRAPHIC_MOD::RESET_ALL << Mod::mvCur(0, 30);
	//sleep_for(2s);
	//print << Mod::mvCur(20, 12) << GRAPHIC_MOD::ITALIC << color::FG::RED << color::BG::WHITE << "Im Blue dabidi dabidai" << GRAPHIC_MOD::RESET_ALL << Mod::mvCur(0, 30);
	//sleep_for(2s);
	//print << Mod::clearPath(20, 12, 60);
	disableRawMode();
}