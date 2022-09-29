#pragma once

#include <mutex>  // lock_guard
#include <rtc/print.h>  // printable
#include <ostream>


namespace tmcppc::logging::v2 {
    class logger {
    public:
        static logger& get_instance() {
            static logger instance;
            return instance;
        }

        logger(const logger& rhs) = delete;
        logger(logger&& rhs) = delete;
        logger& operator=(const logger& rhs) = delete;
        logger& operator=(logger&& rhs) = delete;
        ~logger() = default;

        // Let's print a variadic list of printable arguments instead
        void log(std::ostream& os, rtc::print::printable auto ... messages) {
            std::lock_guard<std::mutex> lock{ m_ };
            (os << ... << messages);
        }

    private:
        std::mutex m_{};

        logger() {};
    };
}  // namespace tmcppc::logging::v2
