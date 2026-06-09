#include "ctui.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

using namespace ctui;

static void debuglog(const Widget* wid, const char* title)
{
#ifdef _WIN32
	OutputDebugStringA("\n\n\nDEBUG of ");
	OutputDebugStringA(title);
	OutputDebugStringA(":");
	OutputDebugStringA("\nDESIRED: ");
	OutputDebugStringA("\nX: ");
	OutputDebugStringA(std::to_string(wid->_desired_bounds.x.value_or(-1)).c_str());
	OutputDebugStringA("\nY: ");
	OutputDebugStringA(std::to_string(wid->_desired_bounds.y.value_or(-1)).c_str());
	OutputDebugStringA("\nWIDTH: ");
	OutputDebugStringA(std::to_string(wid->_desired_bounds.width.value_or(-1)).c_str());
	OutputDebugStringA("\nHEIGHT: ");
	OutputDebugStringA(std::to_string(wid->_desired_bounds.height.value_or(-1)).c_str());
	OutputDebugStringA("\nACTUAL: ");
	OutputDebugStringA("\nX: ");
	OutputDebugStringA(std::to_string(wid->_actual_bounds.x.value_or(-1)).c_str());
	OutputDebugStringA("\nY: ");
	OutputDebugStringA(std::to_string(wid->_actual_bounds.y.value_or(-1)).c_str());
	OutputDebugStringA("\nWIDTH: ");
	OutputDebugStringA(std::to_string(wid->_actual_bounds.width.value_or(-1)).c_str());
	OutputDebugStringA("\nHEIGHT: ");
	OutputDebugStringA(std::to_string(wid->_actual_bounds.height.value_or(-1)).c_str());
#endif
}

int main() {
	enable_raw_mode();
	auto main = VStack(&screen, pady = 3, halign=Align::Start);

	auto c = Label(&main, text = "asd");
	auto d = Label(&main, text = "2test");

	main.render();
	debuglog(&main, "Main VStack");
	debuglog(&c, "C Label");
	disable_raw_mode();
}