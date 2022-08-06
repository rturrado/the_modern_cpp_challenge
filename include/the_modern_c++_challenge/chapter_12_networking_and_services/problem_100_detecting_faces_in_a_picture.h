#pragma once

#include "chapter_12_networking_and_services/face_detection.h"

#include <iosfwd>


namespace tmcppc::problem_100 {
    void test_face_detection(std::ostream& os, const tmcppc::face_detection::detector& detector);
}  // namespace tmcppc::problem_100


void problem_100_main(std::istream& is, std::ostream& os);
void problem_100_main();
