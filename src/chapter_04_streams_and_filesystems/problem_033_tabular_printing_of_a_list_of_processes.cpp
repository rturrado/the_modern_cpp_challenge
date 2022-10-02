#include "chapter_04_streams_and_filesystems/problem_033_tabular_printing_of_a_list_of_processes.h"

#include <algorithm>  // max
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <numeric>  // accumulate
#include <string>  // string_literals, to_string
#include <vector>

using namespace tmcppc::process;


namespace tmcppc::problem_33 {
    void print_process_infos(std::ostream& os, std::vector<info>& infos) {
        auto id_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0),
            [](auto total_max, const auto& info) {
                total_max = std::max(total_max, std::to_string(info.id()).size());
                return total_max;
            }) };
        auto name_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0),
            [](auto total_max, const auto& info) {
                total_max = std::max(total_max, info.name().size());
                return total_max;
            }) };
        auto status_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0),
            [](auto total_max, const auto& info) {
                total_max = std::max(total_max, to_string(info.status()).size());
                return total_max;
            }) };
        auto account_name_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0),
            [](auto total_max, const auto& info) {
                total_max = std::max(total_max, info.account_name().size());
                return total_max;
            }) };
        auto mem_size_b_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0),
            [](auto total_max, const auto& info) {
                total_max = std::max(total_max, std::to_string(info.mem_size_b() / 1024).size());
                return total_max;
            }) };
        auto platform_max_width{ std::accumulate(cbegin(infos), cend(infos), static_cast<size_t>(0),
            [](auto total_max, const auto& info) {
                total_max = std::max(total_max, to_string(info.platform()).size());
                return total_max;
            }) };

        std::ranges::sort(infos, {}, [](const auto& info) { return info.name(); });

        bool first{ true };
        for (auto& info : infos) {
            fmt::print(os, "{}{:<{}} {:{}} {:{}} {:{}} {:>{}} {:{}}",
                first ? "" : "\n",
                info.id(), id_max_width,
                info.name(), name_max_width,
                to_string(info.status()), status_max_width,
                info.account_name(), account_name_max_width,
                info.mem_size_b() / 1024, mem_size_b_max_width,
                to_string(info.platform()), platform_max_width);
            first = false;
        }
    }
}  // namespace tmcppc::problem_33


void problem_33_main(std::ostream& os) {
    using namespace tmcppc::problem_33;

    std::vector<info> infos{
       { 512, "cmd.exe", status_t::running, "SYSTEM", 148293, platform_t::x64 },
       { 1044, "chrome.exe", status_t::running, "marius.bancila", 25180454, platform_t::x32 },
       { 7108, "explorer.exe", status_t::running, "marius.bancila", 2952943, platform_t::x64 },
       { 10100, "chrome.exe", status_t::running, "marius.bancila", 227756123, platform_t::x32 },
       { 22456, "skype.exe", status_t::suspended, "marius.bancila", 16870123, platform_t::x64 },
    };

    print_process_infos(os, infos);

    fmt::print(os, "\n\n");
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
void problem_33_main() {
    problem_33_main(std::cout);
}
