#pragma once

#include <istream>
#include <ostream>


void print_armstrong_numbers_up_to_a_limit_v1(std::ostream& os, size_t n, bool print_results);
void print_armstrong_numbers_up_to_a_limit_v1(size_t n, bool print_results);
void print_armstrong_numbers_up_to_a_limit_v2(std::ostream& os, size_t n, bool print_results);
void print_armstrong_numbers_up_to_a_limit_v2(size_t n, bool print_results);
void print_armstrong_numbers_up_to_a_limit_v3(std::ostream& os, const int n, bool print_results);
void print_armstrong_numbers_up_to_a_limit_v3(const int n, bool print_results);

void print_armstrong_numbers_with_three_digits(std::ostream& os);
void print_armstrong_numbers_with_three_digits();

void problem_8_main(std::istream& is, std::ostream& os);
void problem_8_main();
