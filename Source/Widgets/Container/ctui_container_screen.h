#pragma once
#include <complex>

#include "ctui_container_vstack.h"
#include "ctui_config.h"
#include "ctui_runstage.h"

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
            update_bounds();
            return *this;
        }

        void update_bounds();
        std::pair<int, int> get_bounds() const;

        // Run Loop

        void run(const std::function<void(RunStage)>& stage_callback = [](RunStage) {});

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
