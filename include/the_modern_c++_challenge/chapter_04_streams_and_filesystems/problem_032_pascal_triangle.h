#pragma once

#include <cstdint>  // uint32_t
#include <iosfwd>
#include <vector>


namespace tmcppc::problem_32 {
    using pascal_triangle_t = std::vector<std::vector<std::uint32_t>>;

    pascal_triangle_t pascal_triangle(size_t n);
}  // namespace tmcppc::problem_32

void problem_32_main(std::ostream& os);
