#pragma once

#include <date/date.h>
#include <iosfwd>


namespace tmcppc::problem_44 {
    void print_calendar_month(std::ostream& os, const date::year& y, const date::month& m);
}  // namespace tmcppc::problem_44


void problem_44_main(std::ostream& os);
void problem_44_main();
