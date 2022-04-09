#include "chapter_04_streams_and_filesystems/problem_033_tabular_printing_of_a_list_of_processes.h"

#include <algorithm>  // max
#include <format>
#include <iostream>  // cout
#include <numeric>  // accumulate
#include <ostream>
#include <ranges>  // sort
#include <sstream>  // ostringstream
#include <string>  // string_literals, to_string
#include <vector>


namespace Process
{
    enum class Status : bool { running, suspended };
    enum class Platform : bool { x32, x64 };

    class Info
    {
    public:
        Info(size_t id, std::string name, Status status, std::string account_name, size_t mem_size_b, Platform platform) noexcept
            : id_{ id }, name_{ name }, status_{ status }, account_name_{ account_name }, mem_size_b_{ mem_size_b }, platform_{ platform }
        {}

        [[nodiscard]] size_t id() const noexcept { return id_; }
        [[nodiscard]] std::string name() const noexcept { return name_; }
        [[nodiscard]] Status status() const noexcept { return status_; }
        [[nodiscard]] std::string account_name() const noexcept { return account_name_; }
        [[nodiscard]] size_t mem_size_b() const noexcept { return mem_size_b_; }
        [[nodiscard]] Platform platform() const noexcept { return platform_; }

    private:
        size_t id_{};
        std::string name_{};
        Status status_{};
        std::string account_name_{};
        size_t mem_size_b_{};
        Platform platform_{};
    };

    std::ostream& operator<<(std::ostream& os, const Status& status)
    {
        os << (status == Status::running ? "Running" : "Suspended");
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Platform& platform)
    {
        os << (platform == Platform::x32 ? "32-bit" : "64-bit");
        return os;
    }

    std::string to_string(const Status& status)
    {
        std::ostringstream oss;
        oss << status;
        return oss.str();
    }

    std::string to_string(const Platform& platform)
    {
        std::ostringstream oss;
        oss << platform;
        return oss.str();
    }
}


void print_process_infos(std::vector<Process::Info>& infos)
{
    using namespace Process;

    auto id_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0), [](auto total_max, const auto& info) {
            total_max = std::max(total_max, std::to_string(info.id()).size()); return total_max; }) };
    auto name_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0), [](auto total_max, const auto& info) {
            total_max = std::max(total_max, info.name().size()); return total_max; }) };
    auto status_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0), [](auto total_max, const auto& info) {
            total_max = std::max(total_max, to_string(info.status()).size()); return total_max; }) };
    auto account_name_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0), [](auto total_max, const auto& info) {
            total_max = std::max(total_max, info.account_name().size()); return total_max; }) };
    auto mem_size_b_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0), [](auto total_max, const auto& info) {
            total_max = std::max(total_max, std::to_string(info.mem_size_b() / 1024).size()); return total_max; }) };
    auto platform_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0), [](auto total_max, const auto& info) {
            total_max = std::max(total_max, to_string(info.platform()).size()); return total_max; }) };

    std::ranges::sort(infos, {}, [](const auto& info) { return info.name(); });

    for (auto& info : infos)
    {
        std::cout
            << std::format("{:<{}} {:{}} {:{}} {:{}} {:>{}} {:{}}",
                info.id(), id_max_width,
                info.name(), name_max_width,
                to_string(info.status()), status_max_width,
                info.account_name(), account_name_max_width,
                info.mem_size_b() / 1024, mem_size_b_max_width,
                to_string(info.status()), platform_max_width)
            << "\n";
    }
}


// Tabular printing of a list of processes
//
// Suppose you have a snapshot of the list of all processes in a system.
// The information for each process includes name, identifier, status (which can be either running or suspended),
// account name (under which the process runs), memory size in bytes, and platform (which can be either 32-bit or 64-bit).
// Your task is to write a function that takes such a list of processes and prints them to the console alphabetically, in tabular format.
// All columns must be left aligned, except for the memory column which must be right-aligned.
// The value of the memory size must be displayed in KB.
// The following is an example of the output of this function:
//
// chrome.exe    1044   Running    marius.bancila   25180  32-bit
// chrome.exe    10100  Running    marius.bancila  227756  32-bit
// cmd.exe       512    Running    SYSTEM              48  64-bit
// explorer.exe  7108   Running    marius.bancila   29529  64-bit
// skype.exe     22456  Suspended  marius.bancila     656  64-bit
void problem_33_main()
{
    using namespace std::string_literals;
    using namespace Process;

    std::vector<Info> infos
    {
       { 512, "cmd.exe"s, Status::running, "SYSTEM"s, 148293, Platform::x64 },
       { 1044, "chrome.exe"s, Status::running, "marius.bancila"s, 25180454, Platform::x32 },
       { 7108, "explorer.exe"s, Status::running, "marius.bancila"s, 2952943, Platform::x64 },
       { 10100, "chrome.exe"s, Status::running, "marius.bancila"s, 227756123, Platform::x32 },
       { 22456, "skype.exe"s, Status::suspended, "marius.bancila"s, 16870123, Platform::x64 },
    };

    print_process_infos(infos);

    std::cout << "\n";
}
