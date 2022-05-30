#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/faces.h"
#include "chapter_12_networking_and_services/problem_100_detecting_faces_in_a_picture.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <istream>
#include <ostream>
#include <string>  // getline
#include <variant>  // holds_alternative, get

namespace fs = std::filesystem;


void problem_100_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::face_detection;

    fmt::print(os, "Please enter the Azure face resource key: ");
    std::string key{};
    std::getline(is, key);
    fmt::print(os, "\n");
    detector detector{ key };

    const fs::path input_file_path{ fs::current_path() / "res" / "problem100.jpg" };
    auto result{ detector.detect(os, input_file_path) };
    if (std::holds_alternative<faces_response>(result)) {
        std::get<faces_response>(result).print(os);
    } else {
        std::get<error_response>(result).print(os);
        fmt::print(os, "\n");
    }

    fmt::print(os, "\n");
}


// Detecting faces in a picture
//
// Write a program that can identify people's faces from pictures.
// At a minimum, the program must detect the face area and the gender of the person.
// This information should be printed to the console.
// The pictures must be loaded from the disk.
void problem_100_main() {
    problem_100_main(std::cin, std::cout);
}
