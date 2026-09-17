#include "pch.h"

#include "ctui_signal_guard.h"

#include <csignal>

namespace ctui
{
    SignalGuard::SignalGuard()
    {
        std::signal(SIGINT, signal_handler);
        reset_signal();
    }

    SignalGuard::~SignalGuard()
    {
        std::signal(SIGINT, SIG_DFL);
    }
}
