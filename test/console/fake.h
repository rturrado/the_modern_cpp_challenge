#pragma once

#include "console.h"


namespace tmcppc::system {
    struct console_fake : public console_iface {
        void clear_istream(std::istream& is) const override { is.clear(); }
        void clear_screen() const override {}
    };
}  // namespace tmcppc::system
