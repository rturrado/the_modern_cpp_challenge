#pragma once

#include <filesystem>
#include <ostream>
#include <string>


std::uintmax_t directory_size_b(const std::filesystem::path& p, bool follow_symlinks = false);
std::string directory_size_in_bytes_to_string(uintmax_t n);

void problem_35_main(std::ostream& os);
void problem_35_main();
