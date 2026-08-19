> \[!WARNING\]  
> This project is a work in progress and should not be considered production-ready.
<p align="center">
  <a href="https://github.com/Aintdev/CroissanTUI">
    <img src="./.github/images/croissantui_logo1000.png" alt="CroissanTUI" width="250">
  </a>
</p>

<p align="center">
  <em>
     A C++ TUI framework inspired by
    <a href="https://docs.python.org/3/library/tkinter.html">tkinter</a>,
    easy to learn, fast to code, beginner friendly.
  </em>
</p>

<p align="center">
  <a href="https://github.com/Aintdev/CroissanTUI/blob/main/LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License" style="margin-right: 4px;">
  </a>

  <a href="https://github.com/Aintdev/CroissanTUI">
    <img src="https://img.shields.io/badge/version-development--phase-lightgrey" alt="Dev build" style="margin-right: 4px;">
  </a>

  <a href="https://github.com/Aintdev/CroissanTUI">
    <img src="https://img.shields.io/badge/Build%20from%20source-C%2B%2B20-blue" alt="Build from source: C++20" style="margin-right: 4px;">
  </a>

  <a href="https://github.com/Aintdev/CroissanTUI/releases/latest">
    <img src="https://img.shields.io/badge/Precompiled%20.lib-C%2B%2B17-green" alt="Precompiled .lib: C++17">
  </a>
</p>

---

## Resources
<ul>
  <li>
    <strong>Documentation:</strong>
    <img src="https://img.shields.io/badge/WIP-crimson?style=flat" style="vertical-align: middle;">
  <li>
    <strong>Source:</strong>
    <a href="https://github.com/Aintdev/CroissanTUI">https://github.com/Aintdev/CroissanTUI</a>
  </li>
</ul>

---

CroissanTUI is a easy-to-use C++ `Text User Interface Framework`, written entirely from scratch and inspired by Python's [`tkinter`](https://docs.python.org/3/library/tkinter.html) for cross-platform applications. It has easy usage and a gentle learning curve, making it perfect for smaller projects.

### Key features:

- **KWARGs**: instead of `struct`s like `ButtonConfig` to configure Widgets, CroissanTUI uses `keyword arguments` thats inspired by Python's keyword arguments.
- **Text Modifiers**: different characters and words inside a `Label` can be rendered with different colors without having to create separate widgets, using `TextStream`s as a way to store text data.
    ```cpp
    ctui::Label(&parent, 
        text << "Normal text | " 
            << Color::Red << "Red Text | " 
            << GraphicMod::Italic << "Italic red text |" 
            << GraphicMod::ResetAll << "Normal text") // <- Argument evaluates to a TextStream
    ```
- **Live Updates via Lambdas**: `TextStream` tokens can also be `std::function<std::string()>`, letting a `Label` display live values by capturing a reference to an outside object — e.g. `[&score]() { return std::to_string(score); }` so the text updates automatically whenever the referenced value changes.
    ```cpp
    ctui::Label(&parent, 
        text << "Score: " 
            << [&score]() { return std::string(score); },
        align = End);
    ```

## Built with

| Object | Source build | Precompiled Build |
| ---- | ------------ | ---- |
| C++ Language | **C++20** | **C++17** |
| Python | **3.4.x** | N/A |
| libgrapheme | Vendored | N/A |
| [utf8proc](utf8proc-url) | Submodule | N/A |

> **Note:** The library implementation uses C++20 features internally. The public API is compatible with C++17, so applications linking against the precompiled library only require a C++17 compiler.

## Getting started

1. Clone repository into your `third-party`/`vendor` directory recursively.
```bash
git clone --recursive https://github.com/Aintdev/CroissanTUI.git
```

Choose your preferred installation method

<details>
<summary> Install into your project </summary>

2. After cloning the repository, add the project to your `CMakeLists.txt`. Note: replace `${CMAKE_CURRENT_SOURCE_DIR}/third-party/CroissanTUI` with the path to the `CroissanTUI` repository.

```cmake
# Add CroissanTUI
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/third-party/CroissanTUI"
    "${CMAKE_CURRENT_BINARY_DIR}/CroissanTUI"
)

# Link CroissanTUI
target_link_libraries(MyApp PRIVATE CroissanTUI)
```

3. Run your Projects `CMakeLists.txt`
</details>
<details>
<summary>Install via Sample Project</summary>

2. After cloning the repository, navigate to `CroissanTUI/Scripts/` and run the appropriate setup script for your platform:

   - **Linux:** `Sample-Setup-Linux.sh`
   - **Windows:** `Sample-Setup-Windows.bat`

3. Once CMake has finished configuring the project, navigate to `CroissanTUI/Sample/build/`. You will find the generated project files for your CMake-compatible IDE there.

</details>

### Usage
1. Include the Generated Header File into a Translation Unit.
```cpp
#include <ctui_h>
```
> **Note:** Your IDE may not find the headerfile at first. This is not a problem since it will be created at build time of the libary.

2. Begin coding

<details>
<summary> Expand/Collaps code </summary>

```cpp
// Example code for README.md
#include <ctui_h>

using namespace ctui;
using enum Align;

int main() {
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
#endif
    
    enable_raw_mode();
	screen.config();

    auto root = VStack(&screen, pady = 2, halign = Center, fill = true);

    ctui::Label(&root, 
        text << "Normal text | " 
            << Color::Red << "Red Text | " 
            << GraphicMod::Italic << "Italic red text |" 
            << GraphicMod::ResetAll << "Normal text",
        halign = End);

    bool resized = false;

    while (true)
	{
        auto new_winsize = get_win_size();
		if (new_winsize != win_size)
		{
			win_size = new_winsize;
			screen.update_bounds(); // update screen width and height
			std::cout << "\033[?2026h" << "\033[2J\033[H"; // DEC Private Mode Set & Clear Screen
			resized = true;
		};
        
        root.measure(); // measure all widgets

        root.resolve_bounds();  // add the postions together to let the widgets know their absolute positions

        root.render(); // print to screen
        if (resized)
		{
			resized = false;
			std::cout << "\033[?2026l";
		}
        // future feature: screen.mainloop();
    }
}
```

</details>

<!-- MARKDOWN LINKS & IMAGES -->
[utf8proc-url]: https://github.com/JuliaStrings/utf8proc.git