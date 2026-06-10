#pragma once
// CroissanTUI - Single Header Library
// Auto-generated


namespace ctui {
    enum class GraphicMod {
        RESET_ALL = 0, BOLD = 1, DIM = 2,
        ITALIC = 3, UNDERLINE = 4, BLINK = 5,
        REVERSE = 6, INVISIBLE = 7, STRIKE = 8
    };
    enum class Color {
        BLACK = 0, RED, GREEN,
        YELLOW, BLUE, MAGENTA,
        CYAN, WHITE, DEFAULT = 9
    };
    constexpr int fg_base = 30;
    constexpr int bg_base = 40;

}
#include <utility>

namespace ctui {
    struct CursorPos { int row, col; };
    extern bool raw_mode;
    void enable_raw_mode();
    void disable_raw_mode();
    std::pair<int, int> get_win_size();
}
#include <string>

namespace ctui {
	struct Mod {

		Mod(GraphicMod m);
		Mod(const char(&s)[3], Color c);

		static Mod mv_cur(int x, int y);
		static Mod clear_path(int x_begin, int line, int x_end);

		operator const std::string() const;
	private:
		std::string _code;
		Mod(int x, int y);
		Mod(std::string x);
	};
}
#include <iostream>

namespace ctui {
    struct Stream {
        template<typename T>
        Stream& operator<<(const T& val) {
            if constexpr (std::is_constructible_v<Mod, T>) {
                std::cout << static_cast<std::string>(Mod(val));
            }
            else {
                std::cout << val;
            }
            return *this;
        }
    };
    static Stream print;
}
#include <unordered_map>

namespace ctui {
	struct Key {
        enum class Type {
			Unknown,

			Character,
			Ctrl,

			Tab,
			Backspace,
			Enter,
			Escape,

			ArrowUp,
			ArrowDown,
			ArrowLeft,
			ArrowRight,

			DeleteKey,
			Insert,

			Home,
			End,

			PageUp,
			PageDown,

			F1, F2, F3, F4,
			F5, F6, F7, F8,
			F9, F10, F11, F12
		};
#ifndef _WIN32
        static const std::unordered_map<std::string, Type> sequences;
#endif
        Type type;
        char ch;
    };

    Key read_key();
}

namespace ctui {
	struct Percent {
		long double pct;

		Percent(long double val);

		int to_pixels(int max_width) const;
	};
	Percent operator""_pct(unsigned long long val);
}

#define KWARG(name) \
	struct _tag_##name{}; \
	inline constexpr ctui::detail::_KwargKey<_tag_##name> name{};

#define KWARG_T(name, T) ctui::detail::_Kwarg<_tag_##name, T>

namespace ctui {
	namespace detail {
		template<typename TagName, typename T>
		struct _Kwarg { T value; };

		template<typename TagName>
		struct _KwargKey {
			template<typename T>
			auto operator=(T&& v) const {
				if constexpr (std::is_convertible_v<T, std::string>) {
					return _Kwarg<TagName, std::string> { std::string(v) };
				}
				else {
					return _Kwarg<TagName, std::decay_t<T>> { std::forward<T>(v) };
				}
			}
		};
	}
	enum class Align
	{
		Start,
		Center,
		End
	};

	KWARG(text)
	KWARG(box)
	KWARG(pady)
	KWARG(padx)
	KWARG(focus_index)
	KWARG(fg)
	KWARG(bg)
	KWARG(halign)
	KWARG(valign)
	KWARG(fill)
}

#include <cassert>

#define _CTUIMSG_VSTACK_WRONG_KWARG "Unknown Keyword Argument for VStack!\n\nCheck the error message below and search for:\n\t\t'T=ctui::detail::_Kwarg<_tag_(YOUR_INVALID_ARG)'.\n\n"
#define  _CTUIMSG_VSTACK_NO_PARENT "VStack needs parent and cannot be 'nullptr'. Please use ctui::Screen for root-stack."
#include <optional>

namespace ctui {
	struct Rect {
		std::optional<int> x, y;
		std::optional<int> width, height;

		Rect(int startX, int startY, int boxWidth, int boxHeight);

		Rect(std::optional<int> startX, std::optional<int> startY);
		Rect();
	};
}

namespace ctui {
	struct Container;

	struct Widget {
	protected:
		Widget() : _parent(nullptr), _relative_bounds(std::nullopt, std::nullopt), _absolute_bounds(std::nullopt, std::nullopt) {}
	public:
		Container*	_parent;
		Rect		_relative_bounds;
		Rect		_absolute_bounds;

		virtual void render() = 0;
		virtual bool input(Key key) = 0;
		virtual void resolve_bounds(int startx, int starty) = 0;
		virtual void measure() = 0;
		virtual ~Widget();
	};
}
#include <vector>

namespace ctui {
	struct Container : Widget {
		int _focus_index = 0;
		std::vector<Widget*> _children = {};

		void make_child(Widget* child);
		void remove(Widget* child);

		void render() override;
		~Container() override;
	};
}

namespace ctui
{
	struct Label : Widget
	{
		std::string _text = "";
		Color _bg_color = Color::BLACK;
		Color _fg_color = Color::WHITE;
		bool _fill = false;

		template<typename... Args>
		Label(Container* parent, Args&&... args)
		{
			assert(parent && _CTUIMSG_VSTACK_NO_PARENT);
			if (!parent) throw std::invalid_argument(_CTUIMSG_VSTACK_NO_PARENT);
			parent->make_child(this);
			(apply(std::forward<Args>(args)), ...);
		}

		bool input(Key key) override;
		void render() override;
		void resolve_bounds(int startx, int starty) override;
		void measure() override; // TODO: Implement this and resolve_bounds fix
	private:
		void apply(KWARG_T(text, std::string)	arg)
		{
			_text = arg.value;
			_relative_bounds.width = static_cast<int>(_text.length());
			_relative_bounds.height = 1;
			_relative_bounds.x = _relative_bounds.x.value_or(0);
			_relative_bounds.y = 0;
		}
		void apply(KWARG_T(fill, bool) arg) { _fill = arg.value;  }


	protected:
		template<typename T>
		void apply(T&&) {
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}
	};
}
#include <complex>


namespace ctui
{
	struct VStack : Container
	{
		int _pady = 0;
		Align _align = Align::Start;

	protected:
		VStack() = default;
	public:

		template<typename... Args>
		VStack& config(Args&&... args)
		{
			(apply(std::forward<Args>(args)), ...);
			return *this;
		}

		template<typename... Args>
		VStack(Container* parent, Args&&... args)
		{
			assert(parent && _CTUIMSG_VSTACK_NO_PARENT);
			if (!parent) throw std::invalid_argument(_CTUIMSG_VSTACK_NO_PARENT);
			parent->make_child(this);
			config(args...);
		}

		bool input(Key key) override;

		// getters

		// TODO: Getters :)

	protected:
		void apply(KWARG_T(pady,		int)	arg) { _pady		=	arg.value; }
		void apply(KWARG_T(focus_index,	int)	arg) { _focus_index	=	arg.value; }
		void apply(KWARG_T(halign,		Align)	arg) { _align		=	arg.value; }
		template<typename T>
		void apply(T&&) {
			static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
		}
		bool arrow_handler(Key key);
		void resolve_bounds(int startx, int starty) override;
		void measure() override;
	};
}


namespace ctui
{
    struct Screen : VStack
    {
        static Screen& instance()
        {
            static Screen s_instance;
            return s_instance;
        }

        template<typename... Args>
        Screen& config(Args&&... args)
        {
            (apply(std::forward<Args>(args)), ...);
            auto scr_sz = get_win_size();
            _relative_bounds = Rect(0, 0, scr_sz.first, scr_sz.second);
            _absolute_bounds = _relative_bounds;
            return *this;
        }

        Screen(const Screen&) = delete;
        Screen& operator=(const Screen&) = delete;

        [[deprecated("Do not use screen.render(); Use root_container.render() instead.")]]
        void render() override { VStack::render(); }

    private:
        ctui::Color _background = ctui::Color::BLACK;
        ctui::Color _foreground = ctui::Color::WHITE;


        template<typename T>
        void apply(T&&) {
            static_assert(sizeof(T) == 0, _CTUIMSG_VSTACK_WRONG_KWARG);
        }

        Screen();
    };
    inline Screen& screen = Screen::instance();
}