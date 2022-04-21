#pragma once

#include <chrono>
#include <ostream>

namespace ch = std::chrono;


ch::weekday date_to_weekday(const ch::year_month_day& date);
unsigned int weekday_to_number(const ch::weekday & wd);

void problem_41_main(std::ostream& os);
void problem_41_main();
