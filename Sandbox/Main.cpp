#include "ctui.h"

//
// COMMIT INFO: As i've noticed, i made a huge design flaw in doing the measurements and layout calculations in one so im currently refactoring them
//				into two seperate methods. This way i dont have to fear unexpected behaviour and its more clear what everything currently does while
//				programming.
//

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
	
	enable_raw_mode();
	screen.config();
	auto main = VStack(&screen, pady = 3, halign=Center);
	auto sub = VStack(&main, pady = 5, halign = Start);
	
	auto c = Label(&sub, text = "asd");
	auto d = Label(&sub, text = "2test");

	auto cntrlStack = VStack(&main, pady = 1, halign = Start);
	auto control = Label(&main, text = "CONTROL");

	main.render();
	debuglog(&main, "Main VStack");
	debuglog(&c, "C Label");
	disable_raw_mode();
}