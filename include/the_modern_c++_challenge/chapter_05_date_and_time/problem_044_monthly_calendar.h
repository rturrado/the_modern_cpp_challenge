#pragma once

#include <chrono>
#include <iosfwd>

namespace ch = std::chrono;


void print_calendar_month(std::ostream& os, const ch::year& y, const ch::month& m);

void problem_44_main(std::ostream& os);
void problem_44_main();
