#include "pch.h"
#include "ctui_rect.h"
#include <utility>

namespace ctui {
	Rect::Rect(int startX, int startY)
		: x(std::move(startX)), y(std::move(startY)), width(std::nullopt), height(std::nullopt) {
	}
	Rect::Rect(int startX, int startY, int boxWidth, int boxHeight)
		: x(std::move(startX)), y(std::move(startY)), width(std::move(boxWidth)), height(std::move(boxHeight)) {
	}
}