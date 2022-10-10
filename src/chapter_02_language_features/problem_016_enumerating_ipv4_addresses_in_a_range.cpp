#include "chapter_02_language_features/ipv4.h"
#include "chapter_02_language_features/ipv4_range.h"
#include "chapter_02_language_features/problem_016_enumerating_ipv4_addresses_in_a_range.h"

#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <rtc/console.h>  // clear_istream


// Enumerating IPv4 addresses in a range
// Write a program tha allows the user to input two IPv4 addresses representing a range and
// list all the addresses in that range.
// Extend the structure defined for the previous problem to implement the requested functionality.
void problem_16_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::network;

    // Read range start and end addresses from the console
    ipv4 address_start{};
    ipv4 address_end{};
    bool valid_input{ false };
    while (!valid_input) {
        fmt::print(os, "Please input two IPv4 addresses (range start and end): ");
        is >> address_start;
        if (not is.fail()) {
            is >> address_end;
            if (not is.fail()) {
                if (address_start < address_end) {
                    valid_input = true;
                } else {
                    fmt::print(os, "\tError: range start address is bigger than range end address.\n");
                }
            }
        }
        if (is.fail()) {
            fmt::print(os, "\tError: invalid input.\n");
            is.clear();
        }
    }
    rtc::console::clear_istream(is);

    // List all addresses in the range
    fmt::print(os, "List of all addresses in the range:\n");
    ipv4_range address_range{ address_start, address_end };
    for (const auto& address : address_range) {
        fmt::print(os, "\t{}\n", address);
    }
    fmt::print(os, "\n");
}
