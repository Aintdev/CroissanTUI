#pragma once
#include <chrono>
#include <complex>
#include <csignal>
#include <iostream>

#include "ctui_container_vstack.h"
#include "ctui_config.h"
#include "ctui_raw_mode.h"
#include "ctui_runstage.h"
#include "ctui_signal_guard.h"

namespace ctui
{
    class Screen : public VStack
    {
    public:
        template<typename... Args>
        [[nodiscard]] static std::unique_ptr<Screen> make(Args&&... args)
        {
            return std::unique_ptr<Screen>(new Screen(std::forward<Args>(args)...));
        }

        template<typename... Args>
        Screen& config(Args&&... args)
        {
            VStack::config(std::forward<Args>(args)...);
            update_bounds(get_win_size());
            return *this;
        }

        void update_bounds(const std::pair<int, int>& winsize);

        /**
         * @brief Runs measure on all child widgets without changing bounds of this.
         * @param available_width The maximum width available to the widget.
         * Defaults to `INT_MAX` if no limit is specified which will let the Widget
         * size itself up.
         */
        void measure(int available_width = INT_MAX) override;

		/**
		 * @brief Runs the screen's main event loop using default (no-op) stage callbacks.
		 *
		 * Equivalent to calling run() with a callback that ignores every RunStage.
		 */
		void run()
		{
			run([](RunStage) {});
		}

		/**
		 * @brief Runs the screen's main event loop, invoking the given callback(s) at each stage.
		 *
		 * Enters a loop that measures, resolves, and renders all widgets on every iteration,
		 * and re-clears/redraws the screen whenever the terminal window is resized. Stage
		 * callbacks are invoked before/after each phase, allowing external code to hook into
		 * the render pipeline (e.g. for animations, input handling, or diagnostics).
		 *
		 * @tparam Callback One or more callable types accepting a single RunStage argument.
		 * @param stage_callback One or more callbacks invoked at each RunStage. If multiple
		 *        are given, they are all invoked, in order, at every stage.
		 *
		 * @throws std::logic_error if a screen is already running (only one screen may run
		 *         at a time).
		 *
		 * ### Loop stages (per iteration, in order):
		 * - **PreResize** / **DuringResizeFrame** - only fired if the terminal size changed
		 *   since the last iteration; bounds are updated and the screen is cleared before
		 *   DuringResizeFrame fires.
		 * - **PreMeasure** / **PostMeasure** - around measure(), which sizes all widgets.
		 * - **PreResolve** / **PostResolve** - around resolve_bounds(), which computes each
		 *   widget's absolute position.
		 * - **PreRender** / **PostRender** - around render(), which draws to the terminal.
		 * - **PostResize** - fired once, only on iterations where a resize was handled,
		 *   after synchronized-output mode is turned back off.
		 *
		 * The loop continues while get_running() is true and no termination signal has
		 * been received (get_signal_status()).
		 */
		template<typename... Callback>
		void run(Callback&&... stage_callback)
		{
			if (get_running())
			{
				throw std::logic_error("There cannot be multiple screens running at the same time.");
			}

			SignalGuard sg;
			RawModeGuard rwg;

			auto win_size = get_win_size();
			bool resized = false;

			while (get_running() && !get_signal_status())
			{
				if (auto new_winsize = get_win_size(); new_winsize != win_size)
				{
					(stage_callback(RunStage::PreResize),  ...);

					win_size = new_winsize;
					this->update_bounds(new_winsize); // update screen width and height

					std::cout << "\033[?2026h" << "\033[2J\033[H"; // DEC Private Mode Set & Clear Screen

					resized = true;
					(stage_callback(RunStage::DuringResizeFrame), ...);
				}

				(stage_callback(RunStage::PreMeasure), ...);
				measure(win_size.first); // measure all widgets
				(stage_callback(RunStage::PostMeasure), ...);


				(stage_callback(RunStage::PreResolve), ...);
				resolve_bounds(0, 0);  // add the positions together to let the widgets know their absolute positions
				(stage_callback(RunStage::PostResolve), ...);


				(stage_callback(RunStage::PreRender), ...);
				render(); // print to screen
				(stage_callback(RunStage::PostRender), ...);

				if (resized)
				{
					resized = false;
					std::cout << "\033[?2026l";
					(stage_callback(RunStage::PostResize), ...);
				}
			}
		}
    private:
        template<typename T>
        void apply(T&&) 
		{
            static_assert(sizeof(T) == 0, _CTUIMSG_SCREEN_WRONG_KWARG);
        }

        template<typename... Args>
        Screen(Args&&... args)
        {
            config(std::forward<Args>(args)...);
        }
    };
}
