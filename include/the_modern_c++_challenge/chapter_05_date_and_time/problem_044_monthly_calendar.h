#pragma once

#include <chrono>
#include <iosfwd>


namespace tmcppc::problem_44 {
    void print_calendar_month(std::ostream& os, const std::chrono::year& y, const std::chrono::month& m);
}  // namespace tmcppc::problem_44


void problem_44_main(std::ostream& os);
