#pragma once

#include <iosfwd>
#include <vector>


namespace tmcppc::problem_32 {
    std::vector<std::vector<uint32_t>> pascal_triangle(const size_t n);
}  // namespace tmcppc::problem_32

void problem_32_main(std::ostream& os);
void problem_32_main();
