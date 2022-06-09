#pragma once

#include <chrono>
#include <iosfwd>


namespace tmcppc::problem_42 {
    unsigned int daynum(const std::chrono::year_month_day& date);  // starting from 1

    unsigned int weeknum(const std::chrono::year_month_day& date);  // starting from 1
}  // namespace tmcppc::problem_42


void problem_42_main(std::ostream& os);
void problem_42_main();
