#include "chapter_07_concurrency/problem_065_thread_safe_logging.h"
#include "rtc/print.h"  // printable

#include <chrono>  // chrono_literals
#include <future>  // async
#include <iostream>  // cout
#include <mutex>  // lock_guard
#include <thread>  // sleep_for

class Logger
{
public:
    static Logger& get_instance()
    {
        static Logger instance;
        return instance;
    }

    Logger(const Logger& rhs) = delete;
    Logger(Logger&& rhs) = delete;
    Logger& operator=(const Logger& rhs) = delete;
    Logger& operator=(Logger&& rhs) = delete;
    
    // Let's print a variadic list of printable arguments instead
    void log(printable auto ... messages)
    {
        std::lock_guard<std::mutex> lock(m_);
        (std::cout << ... << messages);
    }

private:
    std::mutex m_{};

    Logger() {}
};

// Thread-safe logging to the console
//
// Write a class that enables components running in different threads to safely print log messages to the console
// by synchronizing access to the standard output stream to guarantee the integrity of the output.
// This logging component should have a method called log() with a string argument representing the message to be printed to the console.
void problem_65_main()
{
    using namespace std::chrono_literals;

    auto logger_1 = []() {
        for (size_t i{ 20 }; i > 0;  i--) {
            Logger::get_instance().log("// This is ", 111, "\n");
            std::this_thread::sleep_for(20ms);
        }};
    auto logger_2 = []() {
        for (size_t i{ 20 }; i > 0;  i--) {
            Logger::get_instance().log("\t\t!! ", 222, " is here\n");
            std::this_thread::sleep_for(15ms);
        }};
    auto logger_3 = []() {
        for (size_t i{ 20 }; i > 0;  i--) {
            Logger::get_instance().log("\t\t\t\t-- ", 333, " THEY CALL ME\n");
            std::this_thread::sleep_for(5ms);
        }};

    auto future_1 = std::async(std::launch::async, logger_1);
    auto future_2 = std::async(std::launch::async, logger_2);
    auto future_3 = std::async(std::launch::async, logger_3);

    future_1.wait();
    future_2.wait();
    future_3.wait();

    std::cout << "\n";
}
