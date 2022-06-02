#pragma once

#include <iosfwd>
#include <vector>


struct AbundantNumberResult {
    size_t number{};
    size_t abundance{};
    std::vector<size_t> divisors{};

    auto operator<=>(const AbundantNumberResult& other) const = default;
};

std::vector<AbundantNumberResult> abundant_numbers_up_to(size_t limit);

void problem_6_main(std::istream& is, std::ostream& os);
void problem_6_main();
