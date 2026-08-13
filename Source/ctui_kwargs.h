#pragma once

#include "ctui_textstream.h"

#include <string>
#include <type_traits>
#include <utility>

#define KWARG(name) \
	struct _tag_##name{}; \
	inline ctui::detail::KwargKey<_tag_##name> name{};

#define KWARG_T(name, T) ctui::detail::Kwarg<_tag_##name, T>

#define KWARG_STREAM(name) \
	struct _tag_##name{}; \
	inline ctui::detail::KwargStreamKey<_tag_##name> name{};

#define KWARG_STREAM_T(name) ctui::detail::KwargStream<_tag_##name>

namespace ctui {
	namespace detail {
		// Kwarg		
		template<typename TagName, typename T>
		struct Kwarg { T value; };

		template<typename TagName>
		struct KwargKey {
			template<typename T>
			auto operator=(T&& v) const {
				if constexpr (std::is_same_v<std::decay_t<T>, const char*> || std::is_same_v<std::decay_t<T>, char*>) {
					return Kwarg<TagName, std::string> { std::string(v) };
				}
				else {
					return Kwarg<TagName, std::decay_t<T>> { std::forward<T>(v) };
				}
			}
		};

		// Stream
		template<typename TagName>
		struct KwargStream
		{
			TextStream value;
			KwargStream& operator<<(TextToken tt)
			{
				value << std::move(tt);
				return *this;
			}
		};
		template<typename TagName>
		struct KwargStreamKey {
			KwargStream<TagName> operator<<(TextToken v) const
			{
				TextStream ts{};
				ts << std::move(v);
				return KwargStream<TagName>{ std::move(ts) };
			}
		};
	}

	KWARG_STREAM(text)
	KWARG(box)
	KWARG(pady)
	KWARG(padx)
	KWARG(focus)
	KWARG(fg)
	KWARG(bg)
	KWARG(halign)
	KWARG(valign)
	KWARG(fill)
	KWARG(wraplength)
}
