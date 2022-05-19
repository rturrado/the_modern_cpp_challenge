#include "chapter_10_archives_images_and_databases/png_writer_wrapper.h"

#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <ostream>

using namespace tmcppc::png;


void paint_romania_flag(png_writer& png_writer) {
    const int image_width{ png_writer.get_width() };
    const int image_height{ png_writer.get_height() };

    const int strip_width{ image_width / 3 };

    const rectangle_2d blue_stripe{ { 1, 1 }, { strip_width, image_height } };
    const rectangle_2d yellow_stripe{ { strip_width + 1, 1 }, { strip_width * 2, image_height } };
    const rectangle_2d red_stripe{ { strip_width * 2 + 1, 1 }, { image_width, image_height } };

    const rgb romanian_flag_blue{ 0.0, 43.0 / 255, 127.0 / 255 };  // Pantone 280c
    const rgb romanian_flag_yellow{ 252.0 / 255, 209.0 / 255, 22.0 / 255 };  // Pantone 116c
    const rgb romanian_flag_red{ 206.0 / 255, 17.0 / 255, 38.0 / 255 };  // Pantone 186c

    png_writer.plot_filled_rectangle(blue_stripe, romanian_flag_blue);
    png_writer.plot_filled_rectangle(yellow_stripe, romanian_flag_yellow);
    png_writer.plot_filled_rectangle(red_stripe, romanian_flag_red);
}


void problem_82_main(std::ostream& os) {
    const auto image_file_path{ create_png_file_path(std::filesystem::temp_directory_path(), "romania_flag") };

    fmt::print(os, "Creating {}...\n\n", image_file_path.generic_string());

    png_writer png_writer(300, 200, 0.0, image_file_path);

    paint_romania_flag(png_writer);
}


// Creating a PNG that represents a national flag
//
// Write a program that generates a PNG file that represents the national flag of Romania.
// The size of the image in pixels, as well as the path to the destination file, should be provided by the user.
void problem_82_main() {
    problem_82_main(std::cout);
}
