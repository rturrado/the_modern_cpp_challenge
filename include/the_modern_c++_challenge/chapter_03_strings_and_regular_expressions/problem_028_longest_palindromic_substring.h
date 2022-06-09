#pragma once

#include <iosfwd>
#include <string_view>


namespace tmcppc::problem_28 {
    bool is_palindrome(std::string_view s);

    std::string_view get_longest_palindromic_substring(std::string_view s);
}  // namespace tmcppc::problem_28


void problem_28_main(std::ostream& os);
void problem_28_main();
