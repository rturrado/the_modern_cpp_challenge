#pragma once

#include <iosfwd>
#include <utility>  // pair
#include <vector>


namespace tmcppc::problem_7 {
    std::vector<std::pair<size_t, size_t>> amicable_numbers_up_to(size_t limit);
}  // namespace tmcppc::problem_7


void problem_7_main(std::ostream& os);
void problem_7_main();

void playing_with_tmp(std::ostream& os);
