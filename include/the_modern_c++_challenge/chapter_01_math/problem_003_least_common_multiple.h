#pragma once

#include <iosfwd>
#include <vector>


namespace tmcppc::problem_3 {
    long lcm(std::ostream& os, std::vector<int> v);
    long lcm(std::vector<int> v);
}  // namespace tmcppc::problem_3


void problem_3_main(std::istream& is, std::ostream& os);
void problem_3_main();
