#include "chapter_07_concurrency/logger.h"
#include "chapter_07_concurrency/problem_065_thread_safe_logging.h"

#include <fmt/ostream.h>
#include <future>  // async
#include <mutex>  // lock_guard
#include <thread>  // sleep_for


// Thread-safe logging to the console
//
// Write a class that enables components running in different threads to safely print log messages to the console
// by synchronizing access to the standard output stream to guarantee the integrity of the output.
// This logging component should have a method called log() with a string argument representing the message to be printed to the console.
void problem_65_main(std::ostream& os) {
    using namespace std::chrono_literals;
    using namespace tmcppc::logging::v2;

    auto logger_1 = [&os]() {
        for (size_t i{ 20 }; i > 0;  i--) {
            logger::get_instance().log(os, "// This is ", 111, "\n");
            std::this_thread::sleep_for(20ms);
        }
    };
    auto logger_2 = [&os]() {
        for (size_t i{ 20 }; i > 0;  i--) {
            logger::get_instance().log(os, "\t\t!! ", 222, " is here\n");
            std::this_thread::sleep_for(15ms);
        }
    };
    auto logger_3 = [&os]() {
        for (size_t i{ 20 }; i > 0;  i--) {
            logger::get_instance().log(os, "\t\t\t\t-- ", 333, " THEY CALL ME\n");
            std::this_thread::sleep_for(5ms);
        }
    };

    auto future_1 = std::async(std::launch::async, logger_1);
    auto future_2 = std::async(std::launch::async, logger_2);
    auto future_3 = std::async(std::launch::async, logger_3);

    future_1.wait();
    future_2.wait();
    future_3.wait();

    fmt::print(os, "\n");
}
