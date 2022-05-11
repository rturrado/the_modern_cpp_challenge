#include "Chapter12_NetworkingAndServices.h"
#include "Chapter12_NetworkingAndServices/FaceDetection.h"
#include "Chapter12_NetworkingAndServices/Faces.h"

#include "rtc/pretty_print.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>
#include <variant>  // holds_alternative, get

namespace fs = std::filesystem;


void problem_100_main(std::ostream& os) {
    using namespace tmcppc::face_detection;

    fmt::print(os, "Please enter the Azure face resource key: ");
    std::string key{}; std::cin >> key; std::cout << "\n";
    detector detector{ key };

    const fs::path input_file_path{ fs::current_path() / "res" / "problem100.jpg" };
    auto result{ detector.detect(input_file_path) };
    if (std::holds_alternative<FacesResponse>(result)) {
        std::get<FacesResponse>(result).print(os);
    } else {
        std::get<ErrorResponse>(result).print(os);
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
    problem_100_main(std::cout);
}
