#pragma once
#include <optional>

namespace ctui {
	/**
	 * @brief A simple Vec4 with x, y, width and height.
	 * 
	 * The attributes of a rect are std::optional and may or may not
	 * be std::nullopt so it can also be used as a Vec2 for x & y 
	 * for width & height.
	 * 
	 * @note All attributes in a Rect should be checked before access.
	 */
	struct Rect {
		std::optional<int> x, y;
		std::optional<int> width, height;
		
		Rect(int startX, int startY, int boxWidth, int boxHeight);

		Rect(std::optional<int> width, std::optional<int> height);

		/// @brief Initializes all values as std::nullopt
		Rect();

		/**
		 * @brief Checks if size values are given 
		 * @return True if both width & height are not std::nullopt
		 * @note Is just a wrapper for `width.has_value() && height.has_value()`
		 *       to make code more readable.
		 */
		bool has_size_values() const;

		/**
		 * @brief Checks if positional values are given
		 * @return True if both x & y are not std::nullopt
		 * @note Is just a wrapper for `x.has_value() && y.has_value()`
		 *       to make code more readable.
		 */
		bool has_pos_values() const;

		/**
		 * @brief Checks if all values are given
		 * @return True if both positional and size values are not std::nullopt
		 * @note Is just a wrapper for `has_size_values() && has_pos_values()`
		 *       to make code more readable.
		 */
		bool has_values() const;
	};
}