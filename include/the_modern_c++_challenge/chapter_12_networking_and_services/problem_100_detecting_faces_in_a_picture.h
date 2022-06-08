#pragma once

#include "chapter_12_networking_and_services/face_detection.h"

#include <iosfwd>

using namespace tmcppc::face_detection;


void test_face_detection(std::ostream& os, detector_adaptor* detector);

void problem_100_main(std::istream& is, std::ostream& os);
void problem_100_main();
