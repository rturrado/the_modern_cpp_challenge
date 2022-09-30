#pragma once

#include "chapter_06_algorithms_and_data_structures/console.h"


namespace tmcppc::system {
    struct console_fake : public console_iface {
        void clear_screen() const override {};
    };
}  // namespace tmcppc::system
