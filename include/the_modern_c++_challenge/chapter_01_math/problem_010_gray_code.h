#pragma once

#include <iosfwd>


namespace tmcppc::problem_10 {
    size_t binary_to_gray(size_t binary);
    size_t gray_to_binary(size_t gray);
}  // namespace tmcppc::problem_10


void problem_10_main(std::ostream& os);
void problem_10_main();
