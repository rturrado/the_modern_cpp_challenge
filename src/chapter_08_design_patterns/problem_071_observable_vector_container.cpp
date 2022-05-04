#include "chapter_08_design_patterns/problem_071_observable_vector_container.h"

#include <fmt/ostream.h>
#include <initializer_list>
#include <iostream>  // cout
#include <memory>  // make_shared
#include <ostream>
#include <string>
#include <utility>  // move


void problem_71_main(std::ostream& os) {
    // Test observable vector constructors
    fmt::print(os, "Creating the observable vectors:\n");
    auto sp_ov_0{ std::make_shared<observable_vector<std::string>>() };
    auto sp_ov_1{ std::make_shared<observable_vector<float>>(5) };
    for (auto i = 0; i < sp_ov_1->size(); ++i) {
        (*sp_ov_1)[i] = 3.14f * i;
    }
    auto sp_ov_2{ std::make_shared<observable_vector<double>>(3, 1.5) };
    const char* cstr{ "Hello, universe!" };
    auto sp_ov_3{ std::make_shared<observable_vector<char>>(cstr + 4, cstr + 8) };
    auto sp_ov_4{ std::make_shared<observable_vector<int>>()};
    fmt::print(os, "\tov_0: {}\n", *sp_ov_0);
    fmt::print(os, "\tov_1: {}\n", *sp_ov_1);
    fmt::print(os, "\tov_2: {}\n", *sp_ov_2);
    fmt::print(os, "\tov_3: {}\n", *sp_ov_3);
    fmt::print(os, "\tov_4: {}\n\n", *sp_ov_4);

    // Concrete observers
    auto sp_co_0{ std::make_shared<concrete_observer_1<std::string>>(os, sp_ov_0) };
    auto sp_co_1{ std::make_shared<concrete_observer_2<float>>(os, sp_ov_1) };
    auto sp_co_2{ std::make_shared<concrete_observer_2<double>>(os, sp_ov_2) };
    auto sp_co_3{ std::make_shared<concrete_observer_1<char>>(os, sp_ov_3) };
    auto sp_co_4{ std::make_shared<concrete_observer_2<int>>(os, sp_ov_4) };

    // Attach concrete observers to observable vectors
    sp_ov_0->attach(sp_co_0);
    sp_ov_1->attach(sp_co_1);
    sp_ov_2->attach(sp_co_2);
    sp_ov_3->attach(sp_co_3);
    sp_ov_4->attach(sp_co_4);

    // Test operations and notifications
    fmt::print(os, "Pushing back on ov_0:\n");
    sp_ov_0->push_back("Tush! Never tell me;");
    sp_ov_0->push_back("I take it much unkindly.");
    fmt::print(os, "\n");

    fmt::print(os, "Copy assigning from ov_3:\n");
    observable_vector<char> ov_char{};  // copy operations don't copy the list of observers
    ov_char = *sp_ov_3;
    ov_char.pop_back();
    fmt::print(os, "\n");

    fmt::print(os, "Move assigning from ov_1:\n");
    observable_vector<float> ov_float{};  // move operations don't copy the list of observers
    ov_float = std::move(*sp_ov_1);
    ov_float.push_back(3.14f);
    fmt::print(os, "\n");

    fmt::print(os, "Copy assigning to ov_3:\n");
    *sp_ov_3 = ov_char;
    fmt::print(os, "\n");

    fmt::print(os, "Move assigning to ov_4:\n");
    *sp_ov_4 = observable_vector<int>(std::initializer_list<int>{ 1, 1, 2, 3, 5 });
    fmt::print(os, "\n");

    fmt::print(os, "Detaching from ov_1:\n");
    sp_ov_0->detach(sp_co_0);
    sp_ov_0->push_back("That thou, Iago, who hast had my purse.");
    fmt::print(os, "\n");
}


// Observable vector container
//
// Write a class template that behaves like a vector but can notify registered parties of internal state changes.
// The class must provide at least the following operations:
//
//   - Various constructors for creating new instances of the class.
//   - operator= to assign values to the container.
//   - push_back() to add a new element at the end of the container.
//   - pop_back() to remove the last element from the container.
//   - clear() to remove all the elements from the container.
//   - size() to return the number of elements from the container.
//   - empty() to indicate whether the container is empty or has elements.
//
// operator=, push_back(), pop_back(), and clear() must notify others of the state changes.
// The notification should include the type of the change, and, when the case,
// the index of the element that was changed (such as added or removed).
void problem_71_main() {
    problem_71_main(std::cout);
}
