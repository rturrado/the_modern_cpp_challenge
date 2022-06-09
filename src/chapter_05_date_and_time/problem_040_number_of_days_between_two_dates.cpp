#include "chapter_05_date_and_time/problem_040_number_of_days_between_two_dates.h"

#include <chrono>
#include <iostream>  // cout
#include <ostream>
#include <utility>  // pair
#include <vector>

namespace ch = std::chrono;


namespace tmcppc::problem_40 {
    int difference_in_days(ch::sys_days start_date, ch::sys_days end_date) {
        return (end_date - start_date).count();
    }
}  // namespace tmcppc::problem_40


void problem_40_main(std::ostream& os) {
    using namespace std::chrono_literals;
    using namespace tmcppc::problem_40;

    auto x{ 2012y / 1 / 24 };
    auto y{ 2013y / 1 / 8 };
    auto a{ 1977y / 5 / 23 };
    auto b{ 2021y / 9 / 23 };

    using vector_of_date_pairs = std::vector<std::pair<ch::year_month_day, ch::year_month_day>>;
    for (const auto& [start_date, end_date] : vector_of_date_pairs{ {x, y}, {y, x}, {a, b}, {b, a} }) {
        os << "First day: " << start_date << "\n";
        os << "Second day: " << end_date << "\n";
        os << "Difference (in days): " << difference_in_days(start_date, end_date) << "\n";
        os << "\n";
    }
}


// Number of days between two dates
//
// Write a function that, given two dates, returns the number of days between the two dates.
// The function should work regardless of the order of the input dates.
void problem_40_main() {
    problem_40_main(std::cout);
}
