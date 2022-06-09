#pragma once

#include <iosfwd>


namespace tmcppc::problem_2 {
    int gcd(std::ostream& os, int m, int n);
    int gcd(int m, int n);
}  // namespace tmcppc::problem_2


void problem_2_main(std::istream& is, std::ostream& os);
void problem_2_main();
