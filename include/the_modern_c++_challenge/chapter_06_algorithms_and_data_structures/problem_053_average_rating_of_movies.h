#pragma once

#include <iosfwd>
#include <map>
#include <string>
#include <vector>


using ratings = std::vector<int>;
using movie_ratings = std::map<std::string, ratings>;

double average_rating(ratings rs);

void problem_53_main(std::ostream& os);
void problem_53_main();
