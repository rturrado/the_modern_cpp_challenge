#pragma once

#include <chrono>
#include <iosfwd>


int difference_in_days(std::chrono::sys_days start_date, std::chrono::sys_days end_date);

void problem_40_main(std::ostream& os);
void problem_40_main();
