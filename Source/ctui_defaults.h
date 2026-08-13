#pragma once
#include "ctui_mod_enum.h"

namespace ctui::defaults
{
	struct WidgetDefaults
	{
		static constexpr Color	kFgColor = Color::WHITE;
		static constexpr Color	kBgColor = Color::BLACK;
		static constexpr bool	kFill = false;
		static constexpr size_t kPady = 0;
		static constexpr size_t kFocusIndex = 0;
		static constexpr Align	kHalign = Align::Center;
		static constexpr Align	kValign = Align::Start;
	};

	struct LabelDefaults : WidgetDefaults
	{
		static constexpr const	char* kText = "";
		static constexpr size_t kLabelWraplength = 0;
		static constexpr size_t kEmptyLabelHeight = 0;
	};
}