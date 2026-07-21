#include "ctui_c.h"
#include "../CroissanTUI/src/ctui_utf8.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif
#include <chrono>

class Timer
{
public:
	Timer() : _start(std::chrono::steady_clock::now()) {}

	void reset()
	{
		_start = std::chrono::steady_clock::now();
	}

	double elapsed_ms() const
	{
		auto now = std::chrono::steady_clock::now();
		return std::chrono::duration<double, std::milli>(now - _start).count();
	}

	double elapsed_us() const
	{
		auto now = std::chrono::steady_clock::now();
		return std::chrono::duration<double, std::micro>(now - _start).count();
	}

private:
	std::chrono::steady_clock::time_point _start;
};

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

#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
	enable_raw_mode();
	screen.config();

	auto main = VStack(&screen, pady = 2, halign = Center, fill = true);

	auto header = VStack(&main, pady = 1, halign = Center);
	auto title = Label(&header, text << Color::CYAN << GraphicMod::BOLD << "=== CTUI Demo ===" << GraphicMod::RESET_ALL);
	auto subtitle = Label(&header, text << Color::WHITE << "v0.1.0 — Testbuild");

	auto sub = VStack(&main, pady = 1, halign = Center);
	auto c = Label(&sub, text << "test hier");
	auto d = Label(&sub, text << "Drücke hier zum loslegen.");

	auto info = VStack(&main, pady = 1, halign = Start);
	auto multi = Label(&info, text
		<< Color::YELLOW << "Zeile 1: kurz\n"
		<< Color::GREEN << "Zeile 2: etwas länger als die erste\n"
		<< Color::MAGENTA << "Zeile 3: und diese hier ist nochmal deutlich länger als die vorherigen beiden\n"
		<< Color::WHITE << GraphicMod::UNDERLINE << "Zeile 4: unterstrichen" << GraphicMod::RESET_ALL
	);

	auto stats = VStack(&main, pady = 0, halign = End); //VStack needs end impl.
	auto fps = Label(&stats, text << Color::RED << "FPS: " << []() -> std::string {
		return std::to_string(60);
		}, halign = End);
	auto mem = Label(&stats, text << Color::BLUE << "MEM: 12.4 MB", halign=End);

	auto control = Label(&main, text << Color::CYAN << GraphicMod::BOLD << "START" << GraphicMod::RESET_ALL);

	auto win_size = get_win_size();
	size_t i = 0;
	while (i < 10)
	{
		Timer* a_time = new Timer();
		main.measure(win_size.first);
		OutputDebugStringA(std::string(("\n\nMeasure-Time: ") + std::to_string(a_time->elapsed_ms())).c_str());
		delete(a_time);

		Timer* b_time = new Timer();
		main.resolve_bounds(0, 0);
		OutputDebugStringA(std::string(("\nResolve-Time: ") + std::to_string(b_time->elapsed_ms())).c_str());
		delete(b_time);

		Timer* c_time = new Timer();
		main.render();
		OutputDebugStringA(std::string(("\nRender-Time: ") + std::to_string(c_time->elapsed_ms())).c_str());
		delete(c_time);
		i++;
	}
	
	debuglog(&main, "Main VStack");
	debuglog(&c, "C Label");
	disable_raw_mode();
}
