#pragma once

#include <filesystem>
#include <iosfwd>


namespace tmcppc::problem_34 {
    std::filesystem::path remove_empty_lines(std::ostream& os, const std::filesystem::path& in_file_path);
}  // namespace tmcppc::problem_34


void problem_34_main(std::ostream& os);
