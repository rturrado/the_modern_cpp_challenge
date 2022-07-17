#include "chapter_09_data_serialization/movies.h"
#include "chapter_09_data_serialization/movies_samples.h"
#include "chapter_10_archives_images_and_databases/console/movies.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream

using namespace tmcppc::movies;
using namespace tmcppc::movies::console;


TEST(from_console, DISABLED_cast) {
    std::istringstream iss{
        "Tom Hanks\n"
        "Forrest Gump\n"
        "Sally Field\n"
        "Mrs. Gump\n"
        "Robin Wright\n"
        "Jenny Curran\n"
        "Mykelti Williamson\n"
        "Bubba Blue\n"
        "quit\n"
    };
    std::ostringstream oss{};
    cast c{};
    from_console(iss, oss, c);
    EXPECT_EQ(c, cast_sample);
}


TEST(from_console, DISABLED_writers) {
    std::istringstream iss{
        "Winston Groom\n"
        "Eric Roth\n"
        "quit\n"
    };
    std::ostringstream oss{};
    writers ws{};
    from_console(iss, oss, ws);
    EXPECT_EQ(ws, writers_sample);
}


TEST(from_console, DISABLED_directors) {
    std::istringstream iss{
        "Robert Zemeckis\n"
        "quit\n"
    };
    std::ostringstream oss{};
    directors ds{};
    from_console(iss, oss, ds);
    EXPECT_EQ(ds, directors_sample);
}


TEST(from_console, DISABLED_movie) {
    std::istringstream iss{
        "Forrest Gump\n"
        "1994\n"
        "202\n"
        "Tom Hanks\n"
        "Forrest Gump\n"
        "Sally Field\n"
        "Mrs. Gump\n"
        "Robin Wright\n"
        "Jenny Curran\n"
        "Mykelti Williamson\n"
        "Bubba Blue\n"
        "quit\n"
        "Robert Zemeckis\n"
        "quit\n"
        "Winston Groom\n"
        "Eric Roth\n"
        "quit\n"
    };
    std::ostringstream oss{};
    movie m{};
    from_console(iss, oss, m);
    EXPECT_EQ(m, movie_with_default_id_sample);
}
