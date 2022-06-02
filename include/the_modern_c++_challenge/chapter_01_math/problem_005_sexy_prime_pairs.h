#pragma once

#include <iosfwd>
#include <utility>  // pair
#include <vector>


std::vector<std::pair<size_t, size_t>> sexy_prime_pairs_up_to(size_t limit);

void problem_5_main(std::istream& is, std::ostream& os);
void problem_5_main();
