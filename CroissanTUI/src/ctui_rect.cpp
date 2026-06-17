#include "pch.h"
#include "ctui_rect.h"

namespace ctui {
	Rect::Rect(int startX, int startY, int boxWidth, int boxHeight)
		: x(startX), y(startY), width(boxWidth), height(boxHeight) {}
	Rect::Rect(std::optional<int> width, std::optional<int> height)
		: x(std::nullopt), y(std::nullopt), width(width), height(height) {}
	Rect::Rect()
		: x(std::nullopt), y(std::nullopt), width(std::nullopt), height(std::nullopt) {}

	bool Rect::has_size_values() const
	{
		return width.has_value() && height.has_value();
	}

	bool Rect::has_pos_values() const
	{
		return x.has_value() && y.has_value();
	}

	bool Rect::has_values() const
	{
		return has_pos_values() && has_size_values();
	}
}
