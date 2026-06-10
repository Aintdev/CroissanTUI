#include "pch.h"
#include "ctui_rect.h"
#include <utility>

namespace ctui {
	Rect::Rect(int startX, int startY, int boxWidth, int boxHeight)
		: x(startX), y(startY), width(boxWidth), height(boxHeight) {}
	Rect::Rect(std::optional<int> startX, std::optional<int> startY)
		: x(startX), y(startY), width(std::nullopt), height(std::nullopt) {}
	Rect::Rect()
		: x(std::nullopt), y(std::nullopt), width(std::nullopt), height(std::nullopt) {}
}