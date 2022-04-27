#include "chapter_06_algorithms_and_data_structures/problem_059_weasel_program.h"

#include <algorithm>  // copy
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>
#include <vector>


void problem_59_main(std::ostream& os) {
    weasel_sequence sequence{ "METHINKS IT IS LIKE A WEASEL" };
    
    while (not sequence.end()) {
        // Create 100 mutations of the current sequence
        std::vector<weasel_sequence> mutations(100, sequence);
        for (auto& seq : mutations) {
            seq.mutate();
        }

        // Choose the mutation that is most similar to the target phrase
        sequence = *std::max_element(std::cbegin(mutations), std::cend(mutations),
            [](const auto& seq_1, const auto& seq_2) { return seq_1.score() < seq_2.score(); }
        );

        fmt::print(os, "{}\n", sequence.str());
    }

    fmt::print(os, "\n");
}


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
void problem_59_main() {
    problem_59_main(std::cout);
}
