#pragma once
#include "ctui_config.h"

namespace ctui
{
    class SignalGuard
    {
    public:
        SignalGuard();

        ~SignalGuard();

        SignalGuard(const SignalGuard&) = delete;
        SignalGuard& operator=(const SignalGuard&) = delete;
        SignalGuard(SignalGuard&&) = delete;
        SignalGuard& operator=(SignalGuard&&) = delete;
    };
}
