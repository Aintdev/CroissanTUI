#pragma once

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace ctui
{
	/**
	 * @brief RAII guard that puts the terminal into raw mode for the lifetime of the object.
	 *
	 * On construction the guard:
	 *  - saves the current terminal state,
	 *  - disables line buffering and input echo (keypresses are delivered immediately),
	 *  - switches to the alternate screen buffer, clears it and hides the cursor.
	 *
	 * On destruction everything is restored: the main screen buffer comes back,
	 * the cursor is shown again and the original terminal mode is reapplied.
	 *
	 * @note Create exactly one instance, ideally at the start of run(). Multiple
	 *       simultaneous guards would save an already-modified state as "original".
	 * @note The guard is neither copyable nor movable.
	 */
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
		/**
		 * @brief Enters raw mode and the alternate screen buffer.
		 * @throws std::system_error if the terminal state cannot be read or changed,
		 *         e.g. when stdin/stdout is redirected or piped and not a real terminal.
		 *         On failure the terminal is left in its original state.
		 */
		RawModeGuard();

		/** @brief Leaves the alternate screen buffer and restores the original terminal mode. */
		~RawModeGuard();


		RawModeGuard(const RawModeGuard&) = delete;
		RawModeGuard& operator=(const RawModeGuard&) = delete;
		RawModeGuard(RawModeGuard&&) = delete;
		RawModeGuard& operator=(RawModeGuard&&) = delete;
	};
}
