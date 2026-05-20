#include "pch.h"
#include "ctui_pct.h"

namespace ctui {
	Percent::Percent(long double val) : pct(val) {}

	int Percent::to_pixels(int max_width) const {
		return static_cast<int>(max_width * this->pct);
	}
	Percent operator""_pct(unsigned long long val) { return Percent(static_cast<double>(val) / 100.0); }

}