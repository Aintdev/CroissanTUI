#include "pch.h"

#include "ctui_signal_guard.h"

#include <csignal>

namespace ctui
{
    SignalGuard::SignalGuard()
    {
        set_running(true);
        reset_signal();
        std::signal(SIGINT, signal_handler);
    }

    SignalGuard::~SignalGuard()
    {
        set_running(false);
        std::signal(SIGINT, SIG_DFL);
    }
}
