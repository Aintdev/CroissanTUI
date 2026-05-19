#pragma once

namespace ctui {
	struct Percent {
		long double pct;

		Percent(long double val);

		int to_pixels(int max_width) const;
	};
	Percent operator""_pct(unsigned long long val);
}