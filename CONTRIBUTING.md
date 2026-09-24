<!-- omit in toc -->
# Contributing to CroissanTUI

> [!NOTE]
> This project is currently not accepting pull requests or external contributions but issues are always welcome.
> I'm still learning and would like to keep the development process and project history under my own control while working toward the first release.
>
> Contributions may be opened once the first release is published.

First off, thanks for taking the time to contribute! ❤️

All types of contributions are encouraged and valued. See the [Table of Contents](#table-of-contents) for different ways to help and details about how this project handles them. Please make sure to read the relevant section before making your contribution. It will make it a lot easier for us maintainers and smooth out the experience for all involved. The community looks forward to your contributions. 🎉

> And if you like the project, but just don't have time to contribute, that's fine. There are other easy ways to support the project and show your appreciation, which we would also be very happy about:
> - Use our framework in your projects.
> - Star the project
> - Tweet about it
> - Refer this project in your project's readme

<!-- omit in toc -->
## Table of Contents

- [Philosophy](#philosophy)
- [Code of Conduct](#code-of-conduct)
- [I Have a Question](#i-have-a-question)
- [I Want To Contribute](#i-want-to-contribute)
  - [Reporting Bugs](#reporting-bugs)
  - [Suggesting Enhancements](#suggesting-enhancements)
  - [Your First Code Contribution](#your-first-code-contribution)
  - [Improving The Documentation](#improving-the-documentation)
  - [Styleguides](#styleguides)
    - [Naming](#naming)
    - [Code Style](#code-style)
  - [Commits](#commits)
  - [Pull-Requests](#pull-requests)
- [Attribution](#attribution)

## Philosophy

Consistency beats cleverness. If something already exists in the codebase, match it — even if you'd do it differently from scratch. If you genuinely think a convention is wrong, open an issue and discuss it before rewriting half the repo.

## Code of Conduct

This project and everyone participating in it is governed by the
[CroissanTUI Code of Conduct](https://github.com/Aintdev/CroissanTUI/blob/master/CODE_OF_CONDUCT.md).
By participating, you are expected to uphold this code. Please report unacceptable behavior
to `aintmee.workmail@gmail.com`.


## I Have a Question

> If you want to ask a question, we assume that you have read the available [Documentation](https://aintdev.github.io/CroissanTUI/).

Before you ask a question, it is best to search for existing [Issues](https://github.com/Aintdev/CroissanTUI/issues) that might help you. In case you have found a suitable issue and still need clarification, you can write your question in this issue. It is also advisable to search the internet for answers first.

If you then still feel the need to ask a question and need clarification, we recommend the following:

- Open an [Issue](https://github.com/Aintdev/CroissanTUI/issues/new).
- Provide as much context as you can about what you're running into.
- Provide project and platform versions (nodejs, npm, etc), depending on what seems relevant.

We will then take care of the issue as soon as possible.

## I Want To Contribute

> ### Legal Notice <!-- omit in toc -->
> When contributing to this project, you must agree that you have authored 100% of the content, that you have the necessary rights to the content and that the content you contribute may be provided under the project licence.

### Reporting Bugs

<!-- omit in toc -->
#### Before Submitting a Bug Report

A good bug report shouldn't leave others needing to chase you up for more information. Therefore, we ask you to investigate carefully, collect information and describe the issue in detail in your report. Please complete the following steps in advance to help us fix any potential bug as fast as possible.

- Make sure that you are using the latest version.
- Determine if your bug is really a bug and not an error on your side e.g. using incompatible environment components/versions (Make sure that you have read the [documentation](https://aintdev.github.io/CroissanTUI/). If you are looking for support, you might want to check [this section](#i-have-a-question)).
- To see if other users have experienced (and potentially already solved) the same issue you are having, check if there is not already a bug report existing for your bug or error in the [bug tracker](https://github.com/Aintdev/CroissanTUI/issues?q=label%3Abug).
- Also make sure to search the internet (including Stack Overflow) to see if users outside of the GitHub community have discussed the issue.
- Collect information about the bug:
  - Stack trace (Traceback)
  - OS, Platform and Version (Windows, Linux, macOS, x86, ARM)
  - Version of the interpreter, compiler, SDK, runtime environment, package manager, depending on what seems relevant.
  - Possibly your input and the output
  - Can you reliably reproduce the issue? And can you also reproduce it with older versions?

<!-- omit in toc -->
#### How Do I Submit a Good Bug Report?

> You must never report security related issues, vulnerabilities or bugs including sensitive information to the issue tracker, or elsewhere in public. Instead sensitive bugs must be sent by email to `aintmee.workmail@gmail.com`.

- Open an [Issue](https://github.com/Aintdev/CroissanTUI/issues/new). (Since we can't be sure at this point whether it is a bug or not, we ask you not to talk about a bug yet and not to label the issue.)
- Explain the behavior you would expect and the actual behavior.
- Please provide as much context as possible and describe the *reproduction steps* that someone else can follow to recreate the issue on their own. This usually includes your code. For good bug reports you should isolate the problem and create a reduced test case.
- Provide the information you collected in the previous section.

Once it's filed:

- The project team will label the issue accordingly.
- A team member will try to reproduce the issue with your provided steps. If there are no reproduction steps or no obvious way to reproduce the issue, the team will ask you for those steps and mark the issue as `needs-repro`. Bugs with the `needs-repro` tag will not be addressed until they are reproduced.
- If the team is able to reproduce the issue, it will be marked `needs-fix`, as well as possibly other tags (such as `critical`), and the issue will be left to be [implemented by someone](#your-first-code-contribution).

### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for CroissanTUI, **including completely new features and minor improvements to existing functionality**. Following these guidelines will help maintainers and the community to understand your suggestion and find related suggestions.

<!-- omit in toc -->
#### Before Submitting an Enhancement

- Make sure that you are using the latest version.
- Read the [documentation](https://aintdev.github.io/CroissanTUI/) carefully and find out if the functionality is already covered, maybe by an individual configuration.
- Perform a [search](https://github.com/Aintdev/CroissanTUI/issues) to see if the enhancement has already been suggested. If it has, add a comment to the existing issue instead of opening a new one.
- Find out whether your idea fits with the scope and aims of the project. It's up to you to make a strong case to convince the project's developers of the merits of this feature. Keep in mind that we want features that will be useful to the majority of our users and not just a small subset. If you're just targeting a minority of users, consider writing an add-on/plugin library.

<!-- omit in toc -->
#### How Do I Submit a Good Enhancement Suggestion?

Enhancement suggestions are tracked as [GitHub issues](https://github.com/Aintdev/CroissanTUI/issues).

- Use a **clear and descriptive title** for the issue to identify the suggestion.
- Provide a **step-by-step description of the suggested enhancement** in as many details as possible.
- **Describe the current behavior** and **explain which behavior you expected to see instead** and why. At this point you can also tell which alternatives do not work for you.
- **Explain why this enhancement would be useful** to most CroissanTUI users. You may also want to point out the other projects that solved it better and which could serve as inspiration.

<!-- You might want to create an issue template for enhancement suggestions that can be used as a guide and that defines the structure of the information to be included. If you do so, reference it here in the description. -->

### Your First Code Contribution
<!-- TODO
include Setup of env, IDE and typical getting started instructions?

-->
#### Requirements
1. C++20
2. Python 3.4.x or newer
3. Latest Doxygen version

#### Cloning
Clone the repository into your directory recursively.
```bash
git clone --recursive https://github.com/Aintdev/CroissanTUI.git
```

#### Setup
After cloning the repository, navigate to `CroissanTUI/Scripts/` and run the appropriate setup script for your platform:

   - **Linux:** `Sample-Setup-Linux.sh`
   - **Windows:** `Sample-Setup-Windows.bat`

Once CMake has finished configuring the project, navigate to `CroissanTUI/Sample/build/`. You will find the generated project files for your CMake-compatible IDE there.

### Improving The Documentation
- **Why, not what.** The code shows *what* happens (good names, clear structure). Comments explain *why*, when it's not obvious.
- **Doc comments for public API**, not line-by-line comments in the body:

```cpp
/**
 * Creates a Widget from type T and gives this ownership.
 * @tparam T Type of Widget.
 * @param args Arguments forwarded to T's constructor, after this
 * Container is passed as the parent.
 * @return Handler for the constructed widget.
 */
template<typename T, typename... Args>
WidgetHandler<T> make_child(Args&&... args) { ... }
```

- **Self-explanatory code needs fewer comments.** Lots of inline comments = signal to structure the code more clearly instead of commenting more.
- **No dead/commented-out code.** Belongs in git history, not the final code.
- **Keep comments up to date.** A stale comment is worse than none.


### Styleguides

#### Naming
| Thing | Convention | Example |
|---|---|---|
| Files | `snake_case` | `ctui_pct.cpp`, `ctui_print.h` |
| Namespaces | `lower_snake` | `namespace ctui { }` |
| Classes / Structs / Enums | `PascalCase` | `VStack`, `Percent` |
| Free functions & static methods | `lower_snake` | `to_pixels()`, `clear_path()` |
| Locals & parameters | `lower_snake` | `max_width`, `def_pad` |
| Private member variables | leading `_` | `_pady`, `_halign`, `_code` |
| `constexpr` constants | `kPrefixCamelCase` | `kDefaultPadding` |
| Macros | `ALL_CAPS` | `KWARG`, `KWARG_T` |
| User-defined literal suffixes | `lower_snake` | `_pct` |

**Why leading underscore for private members?** It's immediately clear on sight that a member is private. Leading underscores followed by a capital letter are reserved by the C++ standard, but a leading underscore alone is perfectly safe when used for private members within class scope.

#### Code Style

**Headers**
- No `using namespace` in headers. Ever.
- Try avoiding mutable globals in headers. If you need a shared instance, try to put it in a `.cpp` and expose it through a function (`global_x()`).
- Include order: system → third-party → project. One blank line between groups.

**Types**
- Prefer `double` for user-facing float types unless you have a specific reason not to — and document that reason.

**Control flow**
- Internal/private functions use `assert()` for precondition checks. These compile away in release — they're for catching your own mistakes during development, not for handling bad user input.

**Documentation**
- When editing/creating public code that has yet to have proper doxygen documentation ([see here](#improving-the-documentation)), you are obligated to update/create that documentation fully.
- When possible, structure or document complex logic in a clear, pseudocode-like way to improve readability, as long as it does not negatively impact performance.
- When editing or creating private code, especially within `.cpp` files, use comments for logic that is not immediately readable.

**Reserved Names**
- Never use identifiers starting with `__` or `_[A-Z]` — those are reserved by the implementation in all scopes. This means `_Focus_index` or `__tmp` are off-limits regardless of access level.

### Commits

Follow [Conventional Commits](https://www.conventionalcommits.org/). The format is:

```
<type>(<scope>): <what you did, imperative>
```

Common types:

| Type | Use for |
|---|---|
| `feat` | New component, new behavior |
| `fix` | Bug fix |
| `refactor` | Internal cleanup with no behavior change |
| `docs` | Comments, README, this file |
| `chore` | Build, CI, dependencies |
| `perf` | Measurable performance improvement |

```
feat(vstack): propagate unhandled keys via bool return
fix(input): guard against empty children before index access
refactor(arrow_handler): extract clamping logic, remove parent callback
```

Keep the subject under 72 characters. Use the body if the *why* isn't obvious from the diff.

### Pull Requests

- One PR per logical change. "Fix bug + add feature + reformat everything" is three PRs.
- Rebase onto `master`, not merge. The history should read like a coherent changelog.
- Mass renames or automated reformats go in their own isolated commit with a clear description — don't bury them in functional changes.
- CI must be green before requesting review.
- If your PR is a draft, mark it as one.

<!-- omit in toc -->
## Attribution
This guide is based on the [contributing.md](https://contributing.md/generator) generator!
