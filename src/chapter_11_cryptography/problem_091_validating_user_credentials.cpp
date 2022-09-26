#include "chapter_11_cryptography/problem_091_validating_user_credentials.h"

#include "fmt/ostream.h"

#include <iostream>  // cin, cout
#include <ostream>


void problem_91_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::crypto;

    login_simulator{ is, os }.run();
    fmt::print(os, "\n");
}


// Validating user credentials
//
// Write a program that simulates the way users authenticate to a secured system.
// In order to log in, a user must be already registered with the system.
// The user enters a username and a password and the program checks if it matches any of its registered users;
// if it does, the user is granted access, otherwise, the operation fails.
// For security reasons, the system must not record the password but use an SHA hash instead.
void problem_91_main() {
    problem_91_main(std::cin, std::cout);
}
