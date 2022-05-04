#include "chapter_08_design_patterns/problem_069_generating_social_security_numbers.h"

#include <chrono>
#include <fmt/ostream.h>
#include <initializer_list>
#include <iostream>  // cout
#include <ostream>


void problem_69_main(std::ostream& os) {
    using namespace std::chrono_literals;

    auto ng{ northeria_ssn_generator::get_instance() };
    auto sg{ southeria_ssn_generator::get_instance() };

    for (auto&& p : std::initializer_list<person>{
        { sex::female, 1970y / January / 1 },
        { sex::female, 1976y / February / 3 },
        { sex::female, 1982y / March / 5 },
        { sex::female, 1988y / May / 8 },
        { sex::female, 1994y / July / 11 },
        { sex::male, 2000y / August / 14 },
        { sex::male, 2006y / September / 18 },
        { sex::male, 2012y / October / 22 },
        { sex::male, 2018y / November / 26 },
        { sex::male, 2021y / December / 31 } }) {

        fmt::print(os, "SSNs for {}: Northerian = {}, and Southerian = {}\n", p, ng.generate(p), sg.generate(p));
    }

    fmt::print(os, "\n");
}


// Generating social security numbers
//
// Write a program that can generate social security numbers for two countries, Northeria and Southeria,
// that have different but similar formats for the numbers:
//
// - In Northeria, the numbers have the format SYYYYMMDDNNNNNC, where
//   S is a digit representing the sex, 9 for females and 7 for males,
//   YYYYMMDD is the birth date,
//   NNNNN is a five-digit random number, unique for a day
//   (meaning that the same number can appear twice for two different dates, but not the same date), and
//   C is a digit picked so that the checksum computed as described later is a multiple of 11.
//
// - In Southeria, the numbers have the format SYYYYMMDDNNNNC, where
//   S is a digit representing the sex, 1 for females and 2 for males,
//   YYYYMMDD is the birth date,
//   NNNN is a four-digit random number, unique for a day, and
//   C is a digit picked so that the checksum computed as described below is a multiple of 10.
//
// The checksum in both cases is a sum of all the digits, each multiplied by its weight
// (the position from the most significant digit to the least).
// For example, the checksum for the Southerian number 12017120134895 is computed as follows:
//
//   crc = 14*1 + 13*2 + 12*0 + 11*1 + 10*7 + 9*1 + 8*2 + 7*0 + 6*1 + 5*3 + 4*4 + 3*8 + 2*9 + 1*5 = 230 = 23*10
void problem_69_main() {
    problem_69_main(std::cout);
}
