#pragma once

#include <ostream>
#include <string>
#include <vector>


using permutations = std::vector<std::string>;

permutations all_permutations_rec(std::string str);
permutations all_permutations(std::string str);

void problem_52_main(std::ostream& os);
void problem_52_main();
