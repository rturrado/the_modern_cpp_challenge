#pragma once

#include <iosfwd>
#include <map>
#include <string>


namespace tmcppc::problem_49 {
    using letter_counts = std::map<char, size_t>;

    letter_counts count_letters(const std::string& in_file);

    void print_histogram(std::ostream& os, const letter_counts& counts);
}  // namespace tmcppc::problem_49


void problem_49_main(std::ostream& os);
void problem_49_main();
