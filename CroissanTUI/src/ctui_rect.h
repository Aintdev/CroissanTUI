#pragma once
#include <optional>

namespace ctui {
	struct Rect {
		int x, y;
		std::optional<int> width, height;

		Rect(int startX, int startY, int boxWidth, int boxHeight);
		Rect(int startX, int startY);
	};
}