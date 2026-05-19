# Contributing to CroissanTUI

CroissanTUI is a TUI component library built around a focused set of conventions. This document covers everything you need to know before touching the codebase — read it once, then forget about it because it'll feel natural.

---

## Philosophy

Consistency beats cleverness. If something already exists in the codebase, match it — even if you'd do it differently from scratch. If you genuinely think a convention is wrong, open an issue and discuss it before rewriting half the repo.

---

## Naming

| Thing | Convention | Example |
|---|---|---|
| Files | `snake_case` | `ctui_pct.cpp`, `ctui_print.h` |
| Namespaces | `lower_snake` | `namespace ctui { }` |
| Classes / Structs / Enums | `PascalCase` | `VStack`, `Percent` |
| Free functions & static methods | `lower_snake` | `to_pixels()`, `clear_path()` |
| Locals & parameters | `lower_snake` | `max_width`, `def_pad` |
| Private member variables | trailing `_` | `width_`, `focus_index_` |
| `constexpr` constants | `kPrefixCamelCase` | `kDefaultPadding` |
| Macros | `ALL_CAPS` | `KWARG`, `KWARG_T` |
| User-defined literal suffixes | `lower_snake` | `_pct` |

**Why trailing underscore for private members?** Leading underscores followed by a capital letter are reserved by the C++ standard in all scopes. Trailing underscores are safe, unambiguous, and grep-friendly.

---

## Code Style

**Headers**
- No `using namespace` in headers. Ever.
- No mutable globals in headers. If you need a shared instance, put it in a `.cpp` and expose it through a function (`global_print()`).
- Include order: system → third-party → project. One blank line between groups.

**Sources**
- Avoid `using namespace` at global scope in `.cpp` files too. A local `using` inside a function body is fine if it genuinely reduces noise.

**Types**
- Prefer `double` for user-facing float types unless you have a specific reason not to — and document that reason.

**Macros**
- `KWARG` invocations always end with a semicolon — or never do. Pick one and apply it everywhere in your change. Do not mix.

**Control flow**
- Internal/private functions use `assert()` for precondition checks. These compile away in release — they're for catching your own mistakes during development, not for handling bad user input.
- Return values over output parameters. If a function can fail, say so in the return type.

---

## Reserved Names

Never use identifiers starting with `__` or `_[A-Z]` — those are reserved by the implementation in all scopes. This means `_Focus_index` or `__tmp` are off-limits regardless of access level.

---

## Commits

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

---

## Pull Requests

- One PR per logical change. "Fix bug + add feature + reformat everything" is three PRs.
- Rebase onto `main`, not merge. The history should read like a coherent changelog.
- Mass renames or automated reformats go in their own isolated commit with a clear description — don't bury them in functional changes.
- CI must be green before requesting review.
- If your PR is a draft, mark it as one.

---

## Tooling

Add a `.clang-format` to the repo root and run it before committing. If there isn't one yet, that's a good first contribution. Same goes for a `clang-tidy` config — naming checks and basic safety lints are low-hanging fruit and save review time.

---

## Bugs & Features

**Bug?** Open an issue with: environment (OS, compiler, build type), exact steps to reproduce, expected vs. actual behavior. A minimal repro is worth a thousand words.

**Feature?** Open an issue before writing code. Describe the problem you're solving, not just the solution. Features without a clear problem statement won't be prioritized.

**Question?** Use Discussions, not Issues.