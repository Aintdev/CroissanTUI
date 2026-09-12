#include <ctui_c.h>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace ctui;
using enum Align;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    enable_raw_mode();
    screen->config();

    auto root = screen->make_child<VStack>(
        pady = 2,
        halign = Center,
        fill = true
    );

    auto my_label = root->make_child<Label>(
        text << "Normal text | "
        << Color::RED << "Red Text | "
        << GraphicMod::ITALIC << "Italic red text | "
        << GraphicMod::RESET_ALL << "Normal text"
        << "\n☺️☺️☺️☺️☺️☺️☺️☺️\n|",
        halign = End
    );

    auto win_size = get_win_size();
    bool resized = false;

    while (true)
    {
        auto new_winsize = get_win_size();
        if (new_winsize != win_size)
        {
            win_size = new_winsize;
            screen->update_bounds(); // update screen width and height
            std::cout << "\033[?2026h" << "\033[2J\033[H"; // DEC Private Mode Set & Clear Screen
            resized = true;
        }

        root->measure(win_size.first); // measure all widgets

        root->resolve_bounds(0, 0);  // add the positions together to let the widgets know their absolute positions

        root->render(); // print to screen
        if (resized)
        {
            resized = false;
            std::cout << "\033[?2026l";
        }
    }
}