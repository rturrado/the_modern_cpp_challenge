#include "problems.h"

#include "rtc/console_read.h"

#include <iostream>  // cout


int main()
{
    problems& problems{ problems::get_instance() };

    while (true)
    {
        auto n{ rtc::console::read_positive_number(
            "Please enter a number (starting from 1): ", 1, problems.size() + static_cast<size_t>(1)) };

        std::cout << "\n[PROBLEM " << n << "]\n";
        problems.execute(n);
    }
}
