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
  </li>
  <li>
    <strong>Source:</strong>
    <a href="https://github.com/Aintdev/CroissanTUI">https://github.com/Aintdev/CroissanTUI</a>
  </li>
</ul>

---

CroissanTUI is an easy-to-use C++ `Text User Interface (TUI) framework` for cross-platform applications, inspired by Python's [`tkinter`](https://docs.python.org/3/library/tkinter.html). It's perfect for smaller projects.

### Key features:

- **Keyword Arguments**: instead of `data objects` like `struct ButtonConfig` to configure widgets, CroissanTUI uses `keyword arguments` inspired by Python's `**kwargs`.
- **Text Modifiers**: different characters and words inside a `Label` can be rendered with different colors without having to create separate widgets, using `TextStream`s as a way to store text data.
    ```cpp
    ctui::Label(&parent, 
        text << "Normal text | " 
            << Color::Red << "Red Text | " 
            << GraphicMod::Italic << "Italic red text |" 
            << GraphicMod::ResetAll << "Normal text") // <- Argument evaluates to a TextStream
    ```
- **Live Updates via Lambdas**: `TextStream` tokens can also be `std::function<std::string()>`, letting a `Label` display live values by capturing a reference to an outside object — e.g. `[&score]() { return std::to_string(score); }` so the displayed value can change without recreating the widget.
    ```cpp
    ctui::Label(&parent, 
        text << "Score: " 
            << [&score]() { return std::to_string(score); },
        align = End);
    ```

## Built with

| Object | Source build | Precompiled Build | Usage |
| ---- | ------------ | ---- | ---- |
| C++ Language | **C++20** or newer  | **C++17** | Compilation |
| Python | **3.4.x** or newer | N/A | Header Generation |
| libgrapheme | Vendored | N/A | Codepoint Iteration |
| [utf8proc](utf8proc-url) | Submodule | N/A | Char-Width Calculation |

> **Note:** The library implementation uses C++20 features internally. The public API is compatible with C++17, so applications linking against the precompiled library only require a C++17 compiler.

## Getting started

1. Clone the repository into your `third-party`/`vendor` directory recursively.
```bash
git clone --recursive https://github.com/Aintdev/CroissanTUI.git
```

2. Choose your preferred installation method

<details>
<summary> Install into your project </summary>

After cloning the repository, add the project to your `CMakeLists.txt`. Note: replace `${CMAKE_CURRENT_SOURCE_DIR}/third-party/CroissanTUI` with the path to the `CroissanTUI` repository.

```cmake
# Add CroissanTUI
add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/third-party/CroissanTUI"
    "${CMAKE_CURRENT_BINARY_DIR}/CroissanTUI"
)

# Link CroissanTUI
target_link_libraries(MyApp PRIVATE CroissanTUI)
```

Then, run your project's `CMake configuration/build`.
</details>
<details>
<summary>Install via Sample Project</summary>

After cloning the repository, navigate to `CroissanTUI/Scripts/` and run the appropriate setup script for your platform:

   - **Linux:** `Sample-Setup-Linux.sh`
   - **Windows:** `Sample-Setup-Windows.bat`

Once CMake has finished configuring the project, navigate to `CroissanTUI/Sample/build/`. You will find the generated project files for your CMake-compatible IDE there.

</details>

### Usage
1. Include the generated header file in a translation unit.
```cpp
#include <ctui_h>
```
> **Note:** Your IDE may not find the header file at first. This is not a problem since it will be created at build time of the library.

2. Begin coding

<details>
<summary> Expand/Collapse code </summary>

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

  auto win_size = get_win_size();
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

    root.resolve_bounds();  // add the positions together to let the widgets know their absolute positions

    root.render(); // print to screen
    if (resized)
    {
      resized = false;
      std::cout << "\033[?2026l";
    }
  }
}
```

</details>

<!-- MARKDOWN LINKS & IMAGES -->
[utf8proc-url]: https://github.com/JuliaStrings/utf8proc.git