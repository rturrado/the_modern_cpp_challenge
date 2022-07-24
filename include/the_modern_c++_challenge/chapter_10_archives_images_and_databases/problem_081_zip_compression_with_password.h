#pragma once

#include <filesystem>
#include <iosfwd>
#include <string>


namespace tmcppc::problem_81 {
    void compare_input_and_output(std::ostream& os, const std::filesystem::path& input_path, const std::filesystem::path& output_path);
    void remove_output(std::istream& is, std::ostream& os, const std::filesystem::path& path);
    void test_zip_lib(std::istream& is, std::ostream& os, const std::string& password = {});
}  // namespace tmcppc::problem_81

void problem_81_main(std::istream& is, std::ostream& os);
void problem_81_main();
