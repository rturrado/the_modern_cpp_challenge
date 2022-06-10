#include "chapter_06_algorithms_and_data_structures/problem_053_average_rating_of_movies.h"

#include <algorithm>  // sort
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <numeric>  // accumulate


namespace tmcppc::problem_53 {
    double average_rating(ratings rs) {
        if (rs.empty()) {
            return double{ 0.0 };
        }

        std::sort(begin(rs), end(rs));

        size_t ratings_to_remove{ static_cast<size_t>(rs.size() * 0.1 + 0.5) };  // removing a 10% instead of a 5%
        rs.erase(begin(rs), begin(rs) + ratings_to_remove);
        rs.erase(end(rs) - ratings_to_remove, end(rs));

        return std::accumulate(begin(rs), end(rs), 0.0) / rs.size();
    }
}  // namespace tmcppc::problem_53


void problem_53_main(std::ostream& os) {
    using namespace tmcppc::problem_53;

    movie_ratings mr = {
        { "The Godfather", { 10, 8, 7, 9, 9, 9, 3, 10, 6 } },
        { "The Godfather II", { 10, 9, 9, 8, 8, 10, 2, 4, 6 } },
        { "The Godfather III", { 9, 7, 7, 8, 8, 9, 8, 4, 5 } }
    };

    fmt::print(os, "Average rating of movies:\n");
    for (const auto& m : mr) {
        fmt::print(os, "\t{}: {:.1f}\n", m.first, average_rating(m.second));
    }
    fmt::print(os, "\n");
}


// Average rating of movies
//
// Write a program that calculates and prints the average rating of a list of movies.
// Each movie has a list of ratings from 1 to 10 (where 1 is the lowest and 10 is the highest rating).
// In order to compute the rating, you must remove 5% of the highest and lowest ratings before computing their average.
// The result must be displayed with a single decimal point.
void problem_53_main() {
    problem_53_main(std::cout);
}
