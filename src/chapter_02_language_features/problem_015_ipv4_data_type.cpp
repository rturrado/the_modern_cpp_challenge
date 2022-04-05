#include "chapter_02_language_features/problem_015_ipv4_data_type.h"
#include "chapter_02_language_features/IPv4.h"
#include "rtc/console_read.h"  // clear_istream

#include <iostream>  // cout


// IPv4 data type
//
// Write a class that represents an IPv4 address.
// Implement the functions required to be able to read and write such addresses from or to the console.
// The user should be able to input values in dotted form, such as 127.0.0.1 or 168.192.0.100.
// This is also the form in which IPv4 addresses should be formatted to an output stream.
void problem_15_main()
{
    while (true)
    {
        // Read an IPv4 address from the console
        IPv4 address{};
        if (std::cin >> address)
        {
            // Output the IPv4 address using the object
            std::cout << "You've entered a valid IPv4 address: " << address << "\n";
        }
        else
        {
            std::cout << "Ooops, that was an invalid IPv4 address\n";
            rtc::console::clear_istream(std::cin);
        }
    }
}
