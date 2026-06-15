#pragma once
#include <optional>

namespace ctui {
	struct Rect {
		std::optional<int> x, y;
		std::optional<int> width, height;
		
		Rect(int startX, int startY, int boxWidth, int boxHeight);

		Rect(std::optional<int> width, std::optional<int> height);
		Rect();

		bool has_size_values() const;
	};
}