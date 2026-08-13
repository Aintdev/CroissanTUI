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

int main() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif

	TestVendorLibs();

	//std::this_thread::sleep_for(std::chrono::seconds(3));

	enable_raw_mode();
	screen.config();

	auto main = VStack(&screen, pady = 2, halign = Center, fill = true);

	auto header = VStack(&main, pady = 1, halign = Center);
	auto title = Label(&header, text << Color::CYAN << GraphicMod::BOLD << "=== CTUI Demo ===" << GraphicMod::RESET_ALL);
	auto subtitle = Label(&header, text << Color::WHITE << "v0.1.0 — Testbuild");

	auto sub = VStack(&main, pady = 1, halign = Center);
	auto d = Label(&sub, text << "Drücke hier zum loslegen.");

	std::string mytext = "Zeile 5: Hier eine Variable als Text!";

	auto info = VStack(&main, pady = 1, halign = Start);
	auto multi = Label(&info, text
		<< Color::YELLOW << "Zeile 1: kurz\n"
		<< Color::GREEN << "Zeile 2: etwas länger als die erste\n"
		<< Color::MAGENTA << "Zeile 3: und diese hier ist nochmal deutlich länger als die vorherigen beiden\n"
		<< Color::WHITE << GraphicMod::UNDERLINE << "Zeile 4: unterstrichen\n"
		<< Color::BG_WHITE << Color::BLACK << mytext << GraphicMod::RESET_ALL
	);

	auto stats = VStack(&main, pady = 0, halign = End); //VStack needs end impl.
	size_t fps_out = 0;
	auto fps_label = Label(&stats, text << Color::RED << "FPS: " << [&fps_out]() -> std::string {
		return std::to_string(fps_out);
		}, halign = End);
	auto mem = Label(&stats, text << Color::BLUE << "MEM: 12.4 MB", halign = End);

	auto currentTime = []() -> std::string
		{
			using namespace std::chrono;

			auto now = system_clock::now();
			auto t = system_clock::to_time_t(now);

			std::tm tm{};
#ifdef _WIN32
			localtime_s(&tm, &t);
#else
			localtime_r(&t, &tm);
#endif

			auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
			auto ns = duration_cast<nanoseconds>(now.time_since_epoch()) % 1000000; // Rest nach den ms

			std::ostringstream oss;
			oss << std::put_time(&tm, "%H:%M:%S")
				<< ':'
				<< std::setw(3) << std::setfill('0') << ms.count()
				<< ':'
				<< std::setw(6) << std::setfill('0') << ns.count();

			return oss.str();
		};
	size_t remaining_seconds = 0u;

	auto time = Label(&stats, text << currentTime << "\nTerminal will close in " << Color::BLUE << [&remaining_seconds]() { return std::to_string(remaining_seconds); } << "s" << Color::WHITE << ".", halign = End);

	Label long_text(&stats, text << "Hello, I am quite a long piece of text and need lots of space and I am very cool and Lennox is a pretty cool dude.\nAlso, I think this program is really well written. And I still need some extra text.");
	//Label long_text(&stats, text << "你好，我是一个相当长的文本，需要很多空间，而且我非常酷，Lennox也是一个很酷的家伙。\n另外，我觉得这个程序写得很酷。而且我还需要一些额外的文本。");

	long_text.config(wraplength = 50);

	std::string ctrltext = "THIS TEXT SHOULD NOT BE HERE";
	auto control = Label(&main, text << Color::CYAN << GraphicMod::BOLD << [&ctrltext]() { return ctrltext; } << GraphicMod::RESET_ALL);
	auto centertest = Label(&main, text << ".....😊😊😊😊😊");

	auto win_size = get_win_size();
	size_t i = 0;
	std::cout << "\033[?1049h" << "\033[?25l";
	size_t fps = 0;
	Timer fps_timer = Timer();

	Timer runtime = Timer();

	bool resized = false;
	const int timer = 60;
	bool first_frame = true;

	while (true)
	{
		auto new_winsize = get_win_size();
		if (new_winsize != win_size)
		{
			win_size = new_winsize;
			screen.update_bounds();
			std::cout << "\033[2J\033[H" << "\033[?2026h";
			resized = true;
		};

		Timer a_time = Timer();
		main.measure(win_size.first);
#ifdef _WIN32
		//OutputDebugStringA(std::string("\n\nMeasure-Time: " + std::to_string(a_time.elapsed_ms())).c_str());
#endif

		Timer b_time = Timer();
		main.resolve_bounds(0, 0);
#ifdef _WIN32
		//OutputDebugStringA(std::string("\nResolve-Time: " + std::to_string(b_time.elapsed_ms())).c_str());
#endif

		Timer c_time = Timer();
		main.render();
		if (resized)
		{
			resized = false;
			std::cout << "\033[?2026l";
		}
#ifdef _WIN32
		//OutputDebugStringA(std::string("\nRender-Time: " + std::to_string(c_time.elapsed_ms())).c_str());
#endif

		++fps;

		remaining_seconds = timer - static_cast<size_t>(runtime.elapsed_ms() / 1000);

		if (fps_timer.elapsed_ms() >= 1000)
		{
			double elapsed = fps_timer.elapsed_ms();
			fps_out = static_cast<size_t>(fps * 1000.0 / elapsed);
			fps = 0;
			fps_timer.reset();
		}

		if (runtime.elapsed_ms() >= timer * 1000)
			break;
		if (first_frame)
		{
			first_frame = false;
			ctrltext = "";
		}
	}
	std::cout << "\033[?25h";
	disable_raw_mode();
}