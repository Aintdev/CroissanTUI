#pragma once
#include <chrono>
#include <complex>
#include <csignal>

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
        std::pair<int, int> get_bounds() const;

        // Run Loop
		void run()
		{
			run([](RunStage) {});
		}

		template<typename... Callback>
		void run(Callback&&... stage_callback)
		{
			if (get_running())
			{
				throw std::logic_error("There cannot be multiple screens running at the same time.");
			}

			RawModeGuard rwg;
			SignalGuard sg;

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
        void render() override { VStack::render(); }
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
