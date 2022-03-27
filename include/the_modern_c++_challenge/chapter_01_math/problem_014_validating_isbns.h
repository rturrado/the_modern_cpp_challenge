#pragma once

#include <istream>
#include <ostream>
#include <string>

bool validate_10_digit_isbn(const std::string& str);
bool validate_13_digit_isbn(const std::string& str);

void problem_14_main(std::istream& is, std::ostream& os);
void problem_14_main();
