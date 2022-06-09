#pragma once

#include <iosfwd>
#include <utility>  // pair
#include <vector>


namespace tmcppc::problem_5 {
    std::vector<std::pair<size_t, size_t>> sexy_prime_pairs_up_to(size_t limit);
}  // namespace tmcppc::problem_5


void problem_5_main(std::istream& is, std::ostream& os);
void problem_5_main();
