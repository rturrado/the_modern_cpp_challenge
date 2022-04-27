#pragma once

#include <fstream>  // ifstream
#include <map>
#include <ostream>


using letter_counts = std::map<char, size_t>;

letter_counts count_letters(std::ifstream& in_file);
void print_histogram(letter_counts& counts);

void problem_49_main(std::ostream& os);
void problem_49_main();
