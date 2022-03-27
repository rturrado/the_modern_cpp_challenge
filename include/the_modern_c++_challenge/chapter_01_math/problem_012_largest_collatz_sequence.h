#pragma once

#include <istream>
#include <ostream>
#include <utility>  // pair

std::pair<size_t, size_t> get_longest_collatz_sequence_v1(size_t limit);

void problem_12_main(std::istream& is, std::ostream& os);
void problem_12_main();
