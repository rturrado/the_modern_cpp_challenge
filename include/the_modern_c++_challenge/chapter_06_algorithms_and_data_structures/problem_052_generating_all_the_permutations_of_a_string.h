#pragma once

#include <iosfwd>
#include <string>
#include <vector>


namespace tmcppc::problem_52 {
    using permutations = std::vector<std::string>;

    permutations all_permutations_rec(std::string str);
    permutations all_permutations(std::string str);
}  // namespace tmcppc::problem_52


void problem_52_main(std::ostream& os);
void problem_52_main();
