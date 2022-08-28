#include "chapter_10_archives_images_and_databases/problem_085_reading_from_an_sqlite_db.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_85_main, output) {
    std::istringstream iss{ "y\n" };
    std::ostringstream oss{};
    problem_85_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Catalog:\n"
        "    Movie:\n"
        "        id: 1\n"
        "        title: The Matrix\n"
        "        year: 1999\n"
        "        length: 196\n"
        "        Cast:\n"
        "            Keanu Reeves (Neo)\n"
        "            Laurence Fishburne (Morpheus)\n"
        "            Carrie-Anne Moss (Trinity)\n"
        "            Hugo Weaving (Agent Smith)\n"
        "        Directors:\n"
        "            Lana Wachowski\n"
        "            Lilly Wachowski\n"
        "        Writers:\n"
        "            Lana Wachowski\n"
        "            Lilly Wachowski\n"
        "        Media files: []\n"
        "    Movie:\n"
        "        id: 2\n"
        "        title: Forrest Gump\n"
        "        year: 1994\n"
        "        length: 202\n"
        "        Cast:\n"
        "            Tom Hanks (Forrest Gump)\n"
        "            Sally Field (Mrs. Gump)\n"
        "            Robin Wright (Jenny Curran)\n"
        "            Mykelti Williamson (Bubba Blue)\n"
        "        Directors:\n"
        "            Robert Zemeckis\n"
        "        Writers:\n"
        "            Winston Groom\n"
        "            Eric Roth\n"
        "        Media files: []\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Are you sure you want to remove '.*/movies.db'\\? \\[y/n\\] "
        "\tOK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
