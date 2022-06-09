#pragma once

#include <iosfwd>
#include <vector>


namespace tmcppc::problem_1 {
    std::vector<size_t> naturals_divisible_by_3_or_5_up_to_limit_v1(size_t limit);
    std::vector<size_t> naturals_divisible_by_3_or_5_up_to_limit_v2(size_t limit);
}  // namespace tmcppc::problem_1


void problem_1_main(std::istream& is, std::ostream& os);
void problem_1_main();
