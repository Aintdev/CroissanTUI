#include "pch.h"

#include "ctui_signal_guard.h"

#include "ctui_config.h"

namespace ctui
{
    SignalGuard::SignalGuard()
    {
        set_running(true);
        reset_signal();
        _prev = std::signal(SIGINT, signal_handler);
    }

    SignalGuard::~SignalGuard()
    {
        set_running(false);
        if (_prev == SIG_ERR)
            std::signal(SIGINT, SIG_DFL);
        else
            std::signal(SIGINT, _prev);
    }
}
