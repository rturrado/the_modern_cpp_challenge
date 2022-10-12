#pragma once

#include "timer.h"

#include <chrono>

namespace ch = std::chrono;


namespace tmcppc::chrono {
    struct timer_fake : public timer_iface {
        void sleep_for([[maybe_unused]] const ch::duration<double>& duration) const override {}
    };
}  // namespace tmcppc::chrono
