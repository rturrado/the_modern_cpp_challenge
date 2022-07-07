#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"
#include "chapter_09_data_serialization/pdf_movies.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <chrono>
#include <filesystem>

using namespace std::chrono_literals;
using namespace tmcppc::movies;
using namespace tmcppc::pdf;
namespace fs = std::filesystem;


TEST(doc, save_to_list_of_2_movies) {
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_2_movies.pdf" };
    extern catalog catalog_of_2_movies;
    movies_doc out_doc{ catalog_of_2_movies };
    out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(10));
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_NE(fs::file_size(temp_file_path), 0);
}


TEST(doc, save_to_list_of_30_movies_with_10_per_page) {
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_30_movies_with_10_per_page.pdf" };
    extern catalog catalog_of_30_movies;
    movies_doc out_doc{ catalog_of_30_movies };
    out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(10));
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_NE(fs::file_size(temp_file_path), 0);
}


TEST(doc, save_to_list_of_50_movies_with_100_per_page) {
    const auto temp_file_path{ std::filesystem::temp_directory_path() / "list_of_50_movies_with_100_per_page.pdf" };
    extern catalog catalog_of_50_movies;
    movies_doc out_doc{ catalog_of_50_movies };
    out_doc.save_to(temp_file_path, std::make_unique<text_list_layouter>(100));
    EXPECT_TRUE(fs::exists(temp_file_path));
    EXPECT_NE(fs::file_size(temp_file_path), 0);
}
