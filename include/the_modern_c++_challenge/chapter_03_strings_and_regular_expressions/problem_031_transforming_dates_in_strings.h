#pragma once

#include <ostream>
#include <string>
#include <string_view>


std::string format_date_v1(const std::string& s);
std::string format_date_v2(std::string_view s);

void problem_31_main(std::ostream& os);
void problem_31_main();
