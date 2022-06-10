#pragma once

#include <iosfwd>
#include <map>
#include <string>
#include <vector>


namespace tmcppc::problem_53 {
    using ratings = std::vector<int>;
    using movie_ratings = std::map<std::string, ratings>;

    double average_rating(ratings rs);
}  // namespace tmcppc::problem_53


void problem_53_main(std::ostream& os);
void problem_53_main();
