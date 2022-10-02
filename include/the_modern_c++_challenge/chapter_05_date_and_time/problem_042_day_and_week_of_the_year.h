#pragma once

#include <date/date.h>
#include <iosfwd>


namespace tmcppc::problem_42 {
    unsigned int daynum(const date::year_month_day& date);  // starting from 1

    unsigned int weeknum(const date::year_month_day& date);  // starting from 1
}  // namespace tmcppc::problem_42


void problem_42_main(std::ostream& os);
void problem_42_main();
