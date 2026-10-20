#pragma once
#include <csignal>

namespace ctui
{
	/**
	 * @brief RAII guard that routes SIGINT (Ctrl+C) to the ctui signal handler
	 *        for the lifetime of the object.
	 *
	 * On construction the guard marks the library as running, clears any pending
	 * signal state and installs ctui's SIGINT handler via std::signal, remembering
	 * the previously installed handler. On destruction the library is marked as
	 * no longer running and the previous handler is reinstalled.
	 * 
	 * @note If installing the handler fails (std::signal returns SIG_ERR), the
	 *       constructor does not throw and will still set ctui's SIGINT handler as
	 *       the active handler. On destruction, the default handler (SIG_DFL) 
	 *       is restored in that case.
	 * @note The guard is neither copyable nor movable.
	 */
    class SignalGuard
    {
        /// Previous handler
        decltype(std::signal(0, nullptr)) _prev;
    public:
        /** @brief Installs the SIGINT handler and stores the previous one. */
        SignalGuard();

		/** @brief Restores the SIGINT handler that was active before construction. */
        ~SignalGuard();

        SignalGuard(const SignalGuard&) = delete;
        SignalGuard& operator=(const SignalGuard&) = delete;
        SignalGuard(SignalGuard&&) = delete;
        SignalGuard& operator=(SignalGuard&&) = delete;
    };
}
