#include "chapter_02_language_features/problem_018_variadic_minimum_function.h"

#include <functional>  // greater
#include <iostream>  // cout
#include <string>


// Minimum function with any number of arguments
//
// Write a function template that can take any number of arguments and returns the minimum value of them all,
// using operator< for comparison.
// Write a variant of the function template that can be parameterized with a binary comparison function
// to use instead of operator<.
void problem_18_main()
{
    test_minimum(1, 7, -3, 42);
    test_minimum("en", "un", "lugar", "de", "la", "Mancha");
    test_minimum(std::string("en"), std::string("un"), std::string("lugar"), std::string("de"), std::string("la"), std::string("Mancha"));
    std::cout << "\n";

    test_compare_with("more_than", more_than<int>,
        1, 7, -3, 42);
    test_compare_with("std::greater", std::greater<std::string>{},
        std::string("en"), std::string("un"), std::string("lugar"), std::string("de"), std::string("la"), std::string("Mancha"));
    std::cout << "\n";
}
