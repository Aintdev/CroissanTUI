#include <ctui_c.h>

using namespace ctui;
using enum Align;

int main() {
    auto screen = Screen::make();

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

    screen->run();
}