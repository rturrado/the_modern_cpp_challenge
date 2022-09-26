#pragma once

#include <iosfwd>
#include <vector>


namespace tmcppc::problem_8 {
    std::vector<size_t> armstrong_numbers_up_to_a_limit_v1(size_t n);
    std::vector<size_t> armstrong_numbers_up_to_a_limit_v2(size_t n);
    std::vector<int> armstrong_numbers_up_to_a_limit_v3(int n);

    std::vector<size_t> armstrong_numbers_with_three_digits();
}  // namespace tmcppc::problem_8


void problem_8_main(std::ostream& os);
void problem_8_main();
