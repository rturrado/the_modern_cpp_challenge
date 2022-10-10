#pragma once

#include "chapter_10_archives_images_and_databases/png/png_writer_wrapper.h"

#include <iosfwd>


namespace tmcppc::problem_83 {
    void paint_gradient_background(tmcppc::png::png_writer& png_writer);
    void paint_random_letters(tmcppc::png::png_writer& png_writer);
    void paint_random_strokes(tmcppc::png::png_writer& png_writer);
    void paint_verification_text(tmcppc::png::png_writer& png_writer);
}  // namespace tmcppc::problem_83


void problem_83_main(std::ostream& os);
