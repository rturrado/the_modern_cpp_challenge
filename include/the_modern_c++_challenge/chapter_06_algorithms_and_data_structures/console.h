#pragma once

#include "rtc/console.h"

#include <memory>  // unique_ptr
#include <stdexcept>  // runtime_error
#include <string_view>
#include <utility>  // move


namespace tmcppc::system {
    struct console_error : public std::runtime_error {
        console_error(std::string_view message)
            : std::runtime_error{ message.data() }
        {}
    };

    struct console_iface {
        virtual ~console_iface() = default;
        virtual void clear_screen() const = 0;
    };

    struct console_impl : public console_iface {
        virtual void clear_screen() const override {
            rtc::console::clear_screen();
        }
    };

    class console {
    public:
        console(std::unique_ptr<console_iface> impl_up)
            : impl_up_{ std::move(impl_up) } {

            if (not impl_up_) {
                throw console_error{ "console is null" };
            }
        }
        void clear_screen() const {
            impl_up_->clear_screen();
        }
    private:
        std::unique_ptr<console_iface> impl_up_;
    };
}  // namespace tmcppc::system
