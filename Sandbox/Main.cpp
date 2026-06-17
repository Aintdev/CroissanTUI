#include "ctui.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

using namespace ctui;
using enum Align;

static void debuglog(const Widget* wid, const char* title)
{
#ifdef _WIN32
	OutputDebugStringA("\n\n\nDEBUG of ");
	OutputDebugStringA(title);
	OutputDebugStringA(":");
	OutputDebugStringA("\nDESIRED: ");
	OutputDebugStringA("\nX: ");
	OutputDebugStringA(std::to_string(wid->_relative_bounds.x.value_or(-1)).c_str());
	OutputDebugStringA("\nY: ");
	OutputDebugStringA(std::to_string(wid->_relative_bounds.y.value_or(-1)).c_str());
	OutputDebugStringA("\nWIDTH: ");
	OutputDebugStringA(std::to_string(wid->_relative_bounds.width.value_or(-1)).c_str());
	OutputDebugStringA("\nHEIGHT: ");
	OutputDebugStringA(std::to_string(wid->_relative_bounds.height.value_or(-1)).c_str());
	OutputDebugStringA("\nACTUAL: ");
	OutputDebugStringA("\nX: ");
	OutputDebugStringA(std::to_string(wid->_absolute_bounds.x.value_or(-1)).c_str());
	OutputDebugStringA("\nY: ");
	OutputDebugStringA(std::to_string(wid->_absolute_bounds.y.value_or(-1)).c_str());
	OutputDebugStringA("\nWIDTH: ");
	OutputDebugStringA(std::to_string(wid->_absolute_bounds.width.value_or(-1)).c_str());
	OutputDebugStringA("\nHEIGHT: ");
	OutputDebugStringA(std::to_string(wid->_absolute_bounds.height.value_or(-1)).c_str());
#endif
}

int main() {
	SetConsoleOutputCP(CP_UTF8);
	std::locale::global(std::locale(""));
	std::cout.imbue(std::locale());

	enable_raw_mode();
	screen.config();

	auto main = VStack(&screen, pady = 2, halign=Center);
	auto sub = VStack(&main, pady = 1, halign = Center);
	
	auto c = Label(&sub, text = "Willkommen zu meinem\nsehr schönem Game!");

	c._lines.emplace_back("Test");

	auto d = Label(&sub, text = "Drücke hier zum loslegen.");

	auto control = Label(&main, text = "START");


	main.measure();
	main.resolve_bounds(0, 0);
	main.render();
	
	debuglog(&main, "Main VStack");
	debuglog(&c, "C Label");
	disable_raw_mode();
}