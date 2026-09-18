#pragma once
#include <csignal>

namespace ctui
{
    class SignalGuard
    {
        decltype(std::signal(0, nullptr)) _prev;
    public:
        SignalGuard();

        ~SignalGuard();

        SignalGuard(const SignalGuard&) = delete;
        SignalGuard& operator=(const SignalGuard&) = delete;
        SignalGuard(SignalGuard&&) = delete;
        SignalGuard& operator=(SignalGuard&&) = delete;
    };
}
