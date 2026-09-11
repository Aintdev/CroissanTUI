#include "ctui_c.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif
#include <chrono>

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <thread>

#include "Grapheme/ctui_graphemeview.h"

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

void TestVendorLibs()
{
	std::string_view test =
		"ASCII abc XYZ 123 | "
		"Emoji 😀 😃 🚀 💩 | "
		"SkinTone 👍🏻 👎🏽 👋🏿 | "
		"Flags 🇩🇪 🇺🇸 🇯🇵 | "
		"Family 👨‍👩‍👧‍👦 | "
		"Couple 👩‍❤️‍💋‍👨 | "
		"Combining é ä ô | "
		"CJK 中文 日本語 한국어 | "
		"ZeroWidth \u200B test | "
		"Line\nBreak\tTab";

	for (Grapheme g : GraphemeView(test))
	{
		printf("Char: %.*s  |  Byte-Count: %d  |  Terminal-Width: %d\n",
			static_cast<int>(g.text.size()), g.text.data(),
			static_cast<int>(g.byte_count()),
			static_cast<int>(g.terminal_width())
		);
	}
}

void addTest(Container& parent)
{
	
}

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif

	enable_raw_mode();
	screen.config();

	auto main = screen.make_child<VStack>(fill=true);

	auto l1 = main.get().make_child<Label>(text << "test");

	main.get().remove(l1);

	l1.config(text << "test2");

	auto win_size = get_win_size();
	std::cout << "\033[?1049h" << "\033[?25l";

	bool resized = false;

	while (true)
	{
		auto new_winsize = get_win_size();

		if (new_winsize != win_size)
		{
			win_size = new_winsize;
			screen.update_bounds();

			std::cout << "\033[2J\033[H\033[?2026h";
			resized = true;
		}

		main.measure(win_size.first);
		main.resolve_bounds(0, 0);
		main.render();

		if (resized)
		{
			resized = false;
			std::cout << "\033[?2026l";
		}
	}

	std::cout << "\033[?25h";
	disable_raw_mode();
}