#include "chapter_12_networking_and_services/face_detection.h"
#include "chapter_12_networking_and_services/faces.h"
#include "chapter_12_networking_and_services/problem_100_detecting_faces_in_a_picture.h"
#include "env.h"

#include "rtc/pretty_print.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cin, cout
#include <istream>
#include <memory>  // make_unique
#include <ostream>
#include <string>  // getline
#include <variant>  // get, holds_alternative

using namespace rtc::pretty_print;
using namespace tmcppc::face_detection;
namespace fs = std::filesystem;


namespace tmcppc::problem_100 {
    void test_face_detection(std::ostream& os, const detector& detector) {
        const fs::path input_file_path{ tmcppc::env::get_instance().get_resource_folder_path() / "faces.jpg" };

        try {
            const auto& result{ detector.detect(input_file_path) };
            if (std::holds_alternative<faces_response>(result)) {
                std::get<faces_response>(result).print(os, indentation{ 1 });
            } else {
                std::get<error_response>(result).print(os, indentation{ 1 });
                fmt::print(os, "\n");
            }
        } catch (const std::exception& ex) {
            fmt::print(os, "\tError: {}\n", ex.what());
        }

        fmt::print(os, "\n");
    }
}  // namespace tmcppc::problem_100


void problem_100_main(std::istream& is, std::ostream& os) {
    using namespace tmcppc::problem_100;

    fmt::print(os, "Please enter the Azure face resource key: ");
    std::string key{};
    std::getline(is, key);
    detector detector{ std::make_unique<provider_azure>(key) };
    test_face_detection(os, detector);
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
