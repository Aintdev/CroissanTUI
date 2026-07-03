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

## Requirements

| Task | C++ Standard |
| ---- | ------------ |
| Build from source | **C++20** |
| Use the precompiled library | **C++17** |

> **Note:** The library implementation uses C++20 features internally. The public API is compatible with C++17, so applications linking against the precompiled library only require a C++17 compiler.

## Installation

> <img src="https://img.shields.io/badge/WIP-crimson?style=flat" style="vertical-align: middle;">

## Quick Start

> <img src="https://img.shields.io/badge/WIP-crimson?style=flat" style="vertical-align: middle;">

