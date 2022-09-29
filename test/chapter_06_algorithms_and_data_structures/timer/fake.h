#pragma once

#include "chapter_06_algorithms_and_data_structures/timer.h"

#include <chrono>

namespace ch = std::chrono;


namespace tmcppc::chrono {
    struct timer_fake : public timer_iface {
        virtual void sleep_for([[maybe_unused]] const ch::duration<double>& duration) const override {}
    };
}  // namespace tmcppc::chrono
