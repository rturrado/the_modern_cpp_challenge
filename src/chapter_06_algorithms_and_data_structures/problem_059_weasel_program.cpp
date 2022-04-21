#include "Chapter6_AlgorithmsAndDataStructures.h"
#include "RtcRandom.h"

#include <algorithm>  // copy, max_element
#include <functional>  // plus
#include <iostream>  // cout
#include <iterator>  // ostream_iterator
#include <numeric>  // transform_reduce
#include <sstream>  // ostringstream
#include <string>
#include <vector>

class WeaselSequence
{
public:
    // Fill data_ randomly
    WeaselSequence(const std::string& target)
        : target_{ target }, data_(target.size(), '\0')
    {
        for (char& c : data_) { c = get_random_letter(); }
    }

    // Choose one element of data_ randomly
    // Fill that element randomly
    void mutate() noexcept { data_[get_random_index()] = get_random_letter(); }

    [[nodiscard]] constexpr size_t size() const noexcept { return target_.size(); }

    // Return number of characters that are equal to the target string
    [[nodiscard]] size_t score() const noexcept
    {
        return std::transform_reduce(
            std::cbegin(data_), std::end(data_), std::cbegin(target_),
            static_cast<size_t>(0),
            std::plus<>{},
            [](char c, char t) { return (c == t) ? 1 : 0; });
    }

    [[nodiscard]] bool end() const noexcept { return score() == size(); }

    [[nodiscard]] std::string str() const noexcept
    {
        std::ostringstream oss{};
        std::copy(std::cbegin(data_), std::cend(data_), std::ostream_iterator<char>(oss));
        return oss.str();
    }

private:
    std::string target_{};
    std::string data_{};

    size_t get_random_index() { return get_random_int(0, static_cast<int>(size()) - 1); }

    static char get_random_letter() { static rtc::random::RandomLetter random_letter_{}; return random_letter_(); }
    static size_t get_random_int(int low, int high) { static rtc::random::RandomInt random_int_{ low, high }; return random_int_(); }
};

// The Weasel program
//
// Write a program that implements Richard Dawkin's weasel computer simulation,
// described in Dawkin's words as follows (The Blind Watchmaker, chapter 3):
//
//     We again use our computer monkey, but with a crucial difference in its program.
//     It again begins by choosing a random sequence of 28 letters, just as before ...
//     it duplicates it repeatedly, but with a certain chance of random error - 'mutation' - in the copying.
//     The computer examines the mutant nonsense phrases, the 'progeny' of the original phrase,
//     and chooses the one which, however slightly, most resembles the target phrase, METHINKS IT IS LIKE A WEASEL.
void problem_59_main()
{
    WeaselSequence sequence{ "METHINKS IT IS LIKE A WEASEL" };
    
    while (not sequence.end())
    {
        // Create 100 mutations of the current sequence
        std::vector<WeaselSequence> mutations(100, sequence);
        for (auto& seq : mutations) { seq.mutate(); }

        // Choose the mutation that is most similar to the target phrase
        sequence = *std::max_element(std::cbegin(mutations), std::cend(mutations),
            [](const auto& seq_1, const auto& seq_2) { return seq_1.score() < seq_2.score(); }
        );

        std::cout << sequence.str() << "\n";
    }

    std::cout << "\n";
}
