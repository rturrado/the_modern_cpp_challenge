#pragma once

#include "chapter_10_archives_images_and_databases/png_writer_wrapper.h"

#include <iosfwd>


namespace tmcppc::problem_82 {
    void paint_romania_flag(tmcppc::png::png_writer& png_writer);
}  // namespace tmcppc::problem_82


void problem_82_main(std::ostream& os);
void problem_82_main();
