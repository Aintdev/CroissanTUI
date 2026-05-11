#include "pch.h"
#include "ctui_pct.h"

namespace ctui {
	Percent::Percent(long double val) : pct(val) {}

	int Percent::toPixels(int maxWidth) const {
		return maxWidth * this->pct;
	}
	Percent operator""_pct(unsigned long long val) { return Percent(double(val) / 100.0); };

}