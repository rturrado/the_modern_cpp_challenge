#pragma once

#include <memory>  // unique_ptr
#include "rtc/console.h"
#include <stdexcept>  // runtime_error
#include <string_view>
#include <utility>  // move


namespace tmcppc::system {
    struct console_error : public std::runtime_error {
        explicit console_error(std::string_view message)
            : std::runtime_error{ message.data() }
        {}
    };

    struct console_iface {
        virtual ~console_iface() = default;
        virtual void clear_istream(std::istream& is) const = 0;
        virtual void clear_screen() const = 0;
    };

    struct console_impl : public console_iface {
        void clear_istream(std::istream& is) const override {
            rtc::console::clear_istream(is);
        }
        void clear_screen() const override {
            rtc::console::clear_screen();
        }
    };

    class console {
    public:
        explicit console(std::unique_ptr<console_iface> impl_up)
            : impl_up_{ std::move(impl_up) } {

            if (not impl_up_) {
                throw console_error{ "console is null" };
            }
        }
        void clear_istream(std::istream& is) const {
            impl_up_->clear_istream(is);
        }
        void clear_screen() const {
            impl_up_->clear_screen();
        }
    private:
        std::unique_ptr<console_iface> impl_up_;
    };
}  // namespace tmcppc::system
