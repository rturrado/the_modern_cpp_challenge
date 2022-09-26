#pragma once

#include "date/date.h"

#include <iosfwd>


namespace tmcppc::problem_40 {
    int difference_in_days(date::year_month_day start_date, date::year_month_day end_date);
}  // namespace tmcppc::problem_40


void problem_40_main(std::ostream& os);
void problem_40_main();
