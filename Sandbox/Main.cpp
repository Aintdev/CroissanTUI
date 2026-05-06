#include "ctui.h"
#include <chrono>
#include <thread>

int main() {
	using namespace std::this_thread;     // sleep_for, sleep_until
	using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
	using std::chrono::system_clock;
	ctui::enableRawMode();
	ctui::print << ctui::Mod::mvCur(20, 12) << ctui::GRAPHIC_MOD::ITALIC << ctui::color::FG::BLUE << ctui::color::BG::WHITE << "Test" << ctui::GRAPHIC_MOD::RESET_ALL << ctui::Mod::mvCur(0, 30);
	sleep_for(2s);
	ctui::print << ctui::Mod::mvCur(20, 12) << ctui::GRAPHIC_MOD::ITALIC << ctui::color::FG::RED << ctui::color::BG::WHITE << "Im Blue dabidi dabidai" << ctui::GRAPHIC_MOD::RESET_ALL << ctui::Mod::mvCur(0, 30);
	sleep_for(2s);
	ctui::print << ctui::Mod::clearPath(20, 12, 60);
	ctui::disableRawMode();
}