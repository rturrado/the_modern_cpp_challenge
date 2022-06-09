#pragma once

#include <chrono>
#include <iosfwd>


namespace tmcppc::problem_40 {
    int difference_in_days(std::chrono::sys_days start_date, std::chrono::sys_days end_date);
}  // namespace tmcppc::problem_40


void problem_40_main(std::ostream& os);
void problem_40_main();
