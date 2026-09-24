#pragma once

#include "ctui_textstream.h"

#include <string>
#include <type_traits>
#include <utility>

/**
 * @brief Declares a named parameter ("kwarg") with a given name.
 *
 * Generates a unique tag type `_tag_<name>` and a global key object `<name>`
 * of type ctui::detail::KwargKey<_tag_<name>>. Using `name = value` on the
 * generated object produces a ctui::detail::Kwarg<_tag_<name>, T> holding
 * the assigned value.
 *
 * @param name Identifier to use as the kwarg name (e.g. fg, bg, padx).
 *
 * @code
 * KWARG(fg)
 * widget(fg = Color::Red);
 * @endcode
 */
#define KWARG(name) \
	struct _tag_##name{}; \
	inline ctui::detail::KwargKey<_tag_##name> name{};

 /**
  * @brief Names the concrete Kwarg<> type produced by KWARG(name) for a given value type.
  *
  * Useful in function signatures or template constraints where the exact
  * kwarg type needs to be spelled out explicitly.
  *
  * @param name Name previously declared via KWARG(name).
  * @param T    Value type held by the kwarg.
  *
  * @code
  * void setColor(KWARG_T(fg, Color) k);
  * @endcode
  *
  * @note Requires `_tag_##name` to be visible in the current scope, i.e. the
  *       corresponding KWARG(name) must have been declared beforehand.
  */
#define KWARG_T(name, T) ctui::detail::Kwarg<_tag_##name, T>

  /**
   * @brief Declares a stream-based named parameter ("kwarg") with a given name.
   *
   * Like KWARG(name), but the resulting key object supports `operator<<` with
   * TextToken values instead of `operator=`, allowing the kwarg's value to be
   * built up as a ctui::TextStream.
   *
   * @param name Identifier to use as the stream kwarg name (e.g. text).
   *
   * @code
   * KWARG_STREAM(text)
   * widget(text << "Hello " << bold("World"));
   * @endcode
   */
#define KWARG_STREAM(name) \
	struct _tag_##name{}; \
	inline ctui::detail::KwargStreamKey<_tag_##name> name{};

   /**
	* @brief Names the concrete KwargStream<> type produced by KWARG_STREAM(name).
	*
	* @param name Name previously declared via KWARG_STREAM(name).
	*
	* @code
	* void setText(KWARG_STREAM_T(text) k);
	* @endcode
	*/
#define KWARG_STREAM_T(name) ctui::detail::KwargStream<_tag_##name>

namespace ctui {
	namespace detail {
		// Kwarg

		/**
		 * @brief Holds the value of a named parameter.
		 *
		 * @tparam TagName Unique tag type identifying the kwarg's name.
		 * @tparam T       Type of the stored value.
		 */
		template<typename TagName, typename T>
		struct Kwarg { T value; };

		/**
		 * @brief Key object used to construct a Kwarg<TagName, T> via `operator=`.
		 *
		 * One instance is created per kwarg name by the KWARG() macro. Assigning
		 * a value to it (`name = value`) yields a Kwarg holding that value.
		 * `const char*`/`char*` arguments are converted to std::string.
		 *
		 * @tparam TagName Unique tag type identifying the kwarg's name.
		 */
		template<typename TagName>
		struct KwargKey {
			/**
			 * @brief Creates a Kwarg<TagName, T> from the given value.
			 *
			 * @tparam T Deduced type of the assigned value.
			 * @param v  Value to store in the resulting Kwarg.
			 * @return   Kwarg<TagName, std::string> if v is a C-string,
			 *           otherwise Kwarg<TagName, std::decay_t<T>>.
			 */
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

		/**
		 * @brief Holds the value of a stream-based named parameter as a TextStream.
		 *
		 * @tparam TagName Unique tag type identifying the kwarg's name.
		 */
		template<typename TagName>
		struct KwargStream
		{
			TextStream value;

			/**
			 * @brief Appends a TextToken to the underlying stream.
			 *
			 * @param tt Token to append.
			 * @return   Reference to *this, for chaining.
			 */
			KwargStream& operator<<(TextToken tt)
			{
				value << std::move(tt);
				return *this;
			}
		};

		/**
		 * @brief Key object used to construct a KwargStream<TagName> via `operator<<`.
		 *
		 * One instance is created per stream kwarg name by the KWARG_STREAM() macro.
		 *
		 * @tparam TagName Unique tag type identifying the kwarg's name.
		 */
		template<typename TagName>
		struct KwargStreamKey {
			/**
			 * @brief Starts building a KwargStream<TagName> from an initial token.
			 *
			 * @param v First token to insert into the stream.
			 * @return  A new KwargStream<TagName> containing v.
			 */
			KwargStream<TagName> operator<<(TextToken v) const
			{
				TextStream ts{};
				ts << std::move(v);
				return KwargStream<TagName>{ std::move(ts) };
			}
		};
	}

	KWARG_STREAM(text)		///< Widget text content, built via streaming TextTokens.
	KWARG(box)				///< Box/border style of a widget.
	KWARG(pady)				///< Vertical padding.
	KWARG(padx)				///< Horizontal padding.
	KWARG(focus)			///< Whether the widget is focused.
	KWARG(fg)				///< Foreground color.
	KWARG(bg)				///< Background color.
	KWARG(halign)			///< Horizontal alignment.
	KWARG(valign)			///< Vertical alignment.
	KWARG(fill)				///< Fill behavior.
	KWARG(wraplength)		///< Line-wrap length for text.
}