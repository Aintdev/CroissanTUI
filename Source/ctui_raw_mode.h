#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace ctui
{
	class RawModeGuard
	{
		// Original Terminal State
#ifdef _WIN32
		HANDLE _stdin;
		HANDLE _stdout;

		DWORD _original_stdin_mode;
		DWORD _original_stdout_mode;
#else
		termios _original;
#endif
		void reset_to_original();
	public:
		RawModeGuard();
		~RawModeGuard();


		RawModeGuard(const RawModeGuard&) = delete;
		RawModeGuard& operator=(const RawModeGuard&) = delete;
		RawModeGuard(RawModeGuard&&) = delete;
		RawModeGuard& operator=(RawModeGuard&&) = delete;
	};
}
