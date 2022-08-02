#pragma once

#include "chapter_12_networking_and_services/face_detection.h"

#include <iosfwd>
#include <memory>  // unique_ptr


namespace tmcppc::problem_100 {
    void test_face_detection(std::ostream& os, std::unique_ptr<tmcppc::face_detection::provider_adaptor> provider);
}  // namespace tmcppc::problem_100


void problem_100_main(std::istream& is, std::ostream& os);
void problem_100_main();
