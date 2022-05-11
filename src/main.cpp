#include "problems.h"

#include "rtc/console.h"

#include <fmt/core.h>
#include <iostream>  // cout


int main()
{
    problems& problems{ problems::get_instance() };

    while (true)
    {
        auto message{fmt::format("What problem do you want to run? Please enter a number (between {} and {}): ",
            1, problems.size())};
        auto n{ rtc::console::read_positive_number(message, 1, static_cast<int>(problems.size() + 1)) };

        fmt::print("\n[PROBLEM {}]\n", n);
        problems.execute(n);
    }
}
