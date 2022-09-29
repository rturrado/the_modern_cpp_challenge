#pragma once

#include <chrono>
#include <memory>  // unique_ptr
#include <stdexcept>  // runtime_error
#include <string_view>
#include <thread>  // sleep_for
#include <utility>  // move

namespace ch = std::chrono;


namespace tmcppc::chrono {
    struct timer_error : public std::runtime_error {
        explicit timer_error(std::string_view message)
            : std::runtime_error{ message.data() }
        {}
    };

    struct timer_iface {
        virtual ~timer_iface() = default;
        virtual void sleep_for(const ch::duration<double>& duration) const = 0;
    };

    struct timer_impl : public timer_iface {
        virtual void sleep_for(const ch::duration<double>& duration) const override {
            std::this_thread::sleep_for(duration);
        }
    };

    class timer {
    public:
        explicit timer(std::unique_ptr<timer_iface> impl_up)
            : impl_up_{ std::move(impl_up) } {

            if (not impl_up_) {
                throw timer_error{ "timer is null" };
            }
        }
        void sleep_for(const ch::duration<double>& duration) const {
            impl_up_->sleep_for(duration);
        }
    private:
        std::unique_ptr<timer_iface> impl_up_;
    };
}  // namespace tmcppc::chrono
