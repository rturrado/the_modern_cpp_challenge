#pragma once

#include <istream>
#include <ostream>
#include <string>


std::string read_n_digit_isbn(std::istream& is, std::ostream& os, size_t n);

bool validate_10_digit_isbn(const std::string& str);
bool validate_13_digit_isbn(const std::string& str);

void problem_14_main(std::istream& is, std::ostream& os);
void problem_14_main();
