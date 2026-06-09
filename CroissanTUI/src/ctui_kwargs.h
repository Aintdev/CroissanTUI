#pragma once

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

