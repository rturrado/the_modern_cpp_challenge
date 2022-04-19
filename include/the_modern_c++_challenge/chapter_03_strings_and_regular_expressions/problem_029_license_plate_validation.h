#pragma once

#include <ostream>
#include <string>
#include <vector>


bool validate_license_plate(const std::string& s);
std::vector<std::string> extract_all_license_plates(const std::string& s);

void problem_29_main(std::ostream& os);
void problem_29_main();
