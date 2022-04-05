#include "chapter_02_language_features/problem_019_adding_a_range_of_values_to_a_container.h"
#include "rtc/print.h"

#include <iostream>  // cout
#include <list>
#include <string>
#include <vector>

using namespace rtc::print;


// Adding a range of values to a container
//
// Write a general-purpose function that can add any number of elements
// to the end of a container that has a method push_back(T&& value).
void problem_19_main()
{
    std::vector<int> v_int{};
    push_back_list(v_int, 10, 20, 30);
    std::cout << v_int << "\n";

    std::vector<std::string> v_str{};
    push_back_list(v_str, "Hey", "Joe!", "Voodoo");
    std::cout << v_str << "\n";

    std::list<float> l_float{};
    push_back_list_v2(l_float, 3.14f, 0.99f, -273.0f);
    std::cout << l_float << "\n";

    std::cout << "\n";
}
