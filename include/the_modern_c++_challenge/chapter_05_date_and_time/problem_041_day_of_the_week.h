#pragma once

#include <chrono>
#include <iosfwd>


namespace tmcppc::problem_41 {
    std::chrono::weekday date_to_weekday(const std::chrono::year_month_day& date);

    unsigned int weekday_to_number(const std::chrono::weekday& wd);
}  // namespace tmcppc::problem_41


void problem_41_main(std::ostream& os);
void problem_41_main();
