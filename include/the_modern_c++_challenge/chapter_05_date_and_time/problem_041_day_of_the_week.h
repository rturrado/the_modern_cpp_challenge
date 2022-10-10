#pragma once

#include <date/date.h>
#include <iosfwd>


namespace tmcppc::problem_41 {
    date::weekday date_to_weekday(const date::year_month_day& date);

    unsigned int weekday_to_number(const date::weekday& wd);
}  // namespace tmcppc::problem_41


void problem_41_main(std::ostream& os);
