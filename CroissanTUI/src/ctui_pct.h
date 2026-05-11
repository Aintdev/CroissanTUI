#pragma once

namespace ctui {
	struct Percent {
		long double pct;

		Percent(long double val);

		int toPixels(int maxWidth) const;
	};
	Percent operator""_pct(unsigned long long val);
}