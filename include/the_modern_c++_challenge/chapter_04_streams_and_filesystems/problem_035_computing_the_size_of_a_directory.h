#pragma once

#include <filesystem>
#include <iosfwd>
#include <string>


namespace tmcppc::problem_35 {
    std::uintmax_t directory_size_b(const std::filesystem::path& p, bool follow_symlinks = false);

    std::string directory_size_in_bytes_to_string(uintmax_t n);
}  // namespace tmcppc::problem_35


void problem_35_main(std::ostream& os);
void problem_35_main();
