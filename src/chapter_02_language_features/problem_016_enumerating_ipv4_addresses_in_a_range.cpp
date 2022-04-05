#include "chapter_02_language_features/problem_016_enumerating_ipv4_addresses_in_a_range.h"
#include "chapter_02_language_features/ipv4.h"
#include "chapter_02_language_features/ipv4_range.h"
#include "rtc/console_read.h"  // clear_istream

#include <iostream>  // cout


namespace P16
{
    void test_IPv4Range()
    {
        // IPv4Range is an l-value
        const IPv4Range range{ IPv4{ "10.10.10.10" }, IPv4{ "10.10.10.15" } };
        for (const auto& address : range)
        {
            std::cout << "\t" << address << "\n";
        }
        std::cout << "\n";

        // IPv4Range is an r-value, but constructed from two IPv4 l-values
        IPv4 a1{ "0.0.0.0" };
        IPv4 a2{ "0.0.0.5" };
        for (auto&& address : IPv4Range{ a1, a2 })
        {
            std::cout << "\t" << address << "\n";
        }
        std::cout << "\n";
        // a2 is still valid
        std::cout << "\t" << a2 << "\n\n";

        // IPv4Range is an r-value, and constructed from two IPv4 r-values
        for (auto&& address : IPv4Range{ IPv4{"15.23.18.200"}, IPv4{"15.23.18.210"} })
        {
            std::cout << "\t" << address << "\n";
        }
        std::cout << "\n";

        // cbegin, cend
        for (auto it = range.cbegin(); it != range.cend(); ++it)
        {
            std::cout << "\t" << *it << "\t" << it->to_ulong() << "\n";
        }
        std::cout << "\n";
    }
}

// Enumerating IPv4 addresses in a range
// Write a program tha allows the user to input two IPv4 addreses representing a range and
// list all the addresses in that range.
// Extend the structure defined for the previous problem to implement the requested functionality.
void problem_16_main()
{
    // Read range start and end addresses from the console
    IPv4 address_start{};
    IPv4 address_end{};
    bool valid_input{ false };
    while (!valid_input)
    {
        std::cout << "Please input two IPv4 addresses (range start and end): ";
        std::cin >> address_start >> address_end;
        if (std::cin.good())
        {
            if (address_start < address_end)
            {
                valid_input = true;
            }
            else
            {
                std::cout << "\tError: range start address is bigger than range end address.\n";
            }
        }
        else
        {
            std::cout << "\tError: invalid input.\n";
            rtc::console::clear_istream(std::cin);
        }
    }

    // List all addresses in the range
    std::cout << "List of all addresses in the range:\n";
    IPv4Range address_range{ address_start, address_end };
    for (const auto& address : address_range)
    {
        std::cout << "\t" << address << "\n";
    }
    std::cout << "\n";

    P16::test_IPv4Range();
}
