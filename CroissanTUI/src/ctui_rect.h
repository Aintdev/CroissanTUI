#pragma once
#include <optional>

namespace ctui {
	struct Rect {
		std::optional<int> x, y;
		std::optional<int> width, height;
		int drawStart = 0;

		Rect(int startX, int startY, int boxWidth, int boxHeight);
		Rect(std::optional<int> startX, std::optional<int> startY);
	};
}