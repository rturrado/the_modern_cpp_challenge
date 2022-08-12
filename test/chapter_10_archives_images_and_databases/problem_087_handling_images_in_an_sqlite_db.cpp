#include "chapter_10_archives_images_and_databases/problem_086_inserting_into_an_sqlite_db.h"
#include "chapter_10_archives_images_and_databases/problem_087_handling_images_in_an_sqlite_db.h"
#include "env.h"

#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_87_main, DISABLED_output) {
    const auto resource_folder_path{ tmcppc::env::get_instance().get_resource_folder_path() };
    std::istringstream iss{ fmt::format(
        // Problem 86 input
        "2\n"  // 2 for File
        "n\n"  // no, I don't want to add Fight Club to the list
        "y\n"  // yes, I want to add Blade Runner to the list
        "q\n"  // quit
        "n\n"  // no, I don't want to remove .*/movies.db

        // Problem 87 input
        "help\n"
        "blah\n"
        "list movie .*Run.*\n"
        "add 3, {0}/db/poster.png, Front cover\n"
        "add 3, {0}/db/citi.jpg, Los Angeles\n"
        "add 3, {0}/db/city.jpg, Los Angeles\n"
        "list media 3\n"
        "remove 2\n"
        "list media 3\n"
        "quit\n"
        "y\n",  // yes, I want to remove .*/movies.db
        resource_folder_path.generic_string()
    )
    };
    std::ostringstream oss{};
    problem_86_main(iss, oss);
    problem_87_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\(help for usage\\) > "  // help
        "Usage:\n"
        "\tlist movie <movie_title_regex>\n"
        "\tlist media <movie_id>\n"
        "\tadd <movie_id>, <media_file_path>, \\[<media_file_description>\\]\n"
        "\tremove <media_id>\n"
        "\thelp\n"
        "\tquit\n"
        "Where:\n"
        "\tmedia_file_description  Optional media file description.\n"
        "\tmedia_file_path         File path pointing to a media file.\n"
        "\tmedia_id                Media ID, as shown when listing a media file.\n"
        "\tmovie_id                Movie ID, as shown when listing a movie.\n"
        "\tmovie_title_regex       Regular expression for a movie title.\n"
        "Examples:\n"
        "\tlist movie \\.\\*The\\.\\*\n"
        "\tlist media 2\n"
        "\tadd 2, .*res/db/poster\\.png, Front cover\n"
        "\tremove 1\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "(help for usage) > "  // blah
        "Error: command not found: blah\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "(help for usage) > "  // list movie .*Run.*
        "Catalog:\n"
        "    Movie:\n"
        "        id: 3\n"
        "        title: Blade Runner\n"
        "        year: 1982\n"
        "        length: 117\n"
        "        Cast:\n"
        "            Harrison Ford (Rick Deckard)\n"
        "            Rutger Hauer (Roy Batty)\n"
        "            Sean Young (Rachael)\n"
        "        Directors:\n"
        "            Ridley Scott\n"
        "        Writers:\n"
        "            Hampton Fancher\n"
        "            David Webb Peoples\n"
        "            Philip K. Dick\n"
        "        Media files: []\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\(help for usage\\) > "  // add 3, <RESOURCE FOLDER PATH>/db/poster.png, Front cover
        "Catalog:\n"
        "    Movie:\n"
        "        id: 1\n"
        "        title: The Matrix\n"
        "        year: 1999\n"
        "        length: 196\n"
        "        Cast:\n"
        "            Keanu Reeves \\(Neo\\)\n"
        "            Laurence Fishburne \\(Morpheus\\)\n"
        "            Carrie-Anne Moss \\(Trinity\\)\n"
        "            Hugo Weaving \\(Agent Smith\\)\n"
        "        Directors:\n"
        "            Lana Wachowski\n"
        "            Lilly Wachowski\n"
        "        Writers:\n"
        "            Lana Wachowski\n"
        "            Lilly Wachowski\n"
        "        Media files: \\[\\]\n"
        "    Movie:\n"
        "        id: 2\n"
        "        title: Forrest Gump\n"
        "        year: 1994\n"
        "        length: 202\n"
        "        Cast:\n"
        "            Tom Hanks \\(Forrest Gump\\)\n"
        "            Sally Field \\(Mrs. Gump\\)\n"
        "            Robin Wright \\(Jenny Curran\\)\n"
        "            Mykelti Williamson \\(Bubba Blue\\)\n"
        "        Directors:\n"
        "            Robert Zemeckis\n"
        "        Writers:\n"
        "            Winston Groom\n"
        "            Eric Roth\n"
        "        Media files: \\[\\]\n"
        "    Movie:\n"
        "        id: 3\n"
        "        title: Blade Runner\n"
        "        year: 1982\n"
        "        length: 117\n"
        "        Cast:\n"
        "            Harrison Ford \\(Rick Deckard\\)\n"
        "            Rutger Hauer \\(Roy Batty\\)\n"
        "            Sean Young \\(Rachael\\)\n"
        "        Directors:\n"
        "            Ridley Scott\n"
        "        Writers:\n"
        "            Hampton Fancher\n"
        "            David Webb Peoples\n"
        "            Philip K\\. Dick\n"
        "        Media files:\n"
        "            Media file:\n"
        "                id: 1\n"
        "                path: '.*res/db/poster\\.png'\n"
        "                description: 'Front cover'\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\(help for usage\\) > "  // add 3, <RESOURCE FOLDER PATH>/db/citi.jpg, Los Angeles
        "Error: media file not found: .*res/db/citi\\.jpg\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\(help for usage\\) > "  // add 3, <RESOURCE FOLDER PATH>/db/city.jpg, Los Angeles\n
        "Catalog:\n"
        "    Movie:\n"
        "        id: 1\n"
        "        title: The Matrix\n"
        "        year: 1999\n"
        "        length: 196\n"
        "        Cast:\n"
        "            Keanu Reeves \\(Neo\\)\n"
        "            Laurence Fishburne \\(Morpheus\\)\n"
        "            Carrie-Anne Moss \\(Trinity\\)\n"
        "            Hugo Weaving \\(Agent Smith\\)\n"
        "        Directors:\n"
        "            Lana Wachowski\n"
        "            Lilly Wachowski\n"
        "        Writers:\n"
        "            Lana Wachowski\n"
        "            Lilly Wachowski\n"
        "        Media files: \\[\\]\n"
        "    Movie:\n"
        "        id: 2\n"
        "        title: Forrest Gump\n"
        "        year: 1994\n"
        "        length: 202\n"
        "        Cast:\n"
        "            Tom Hanks \\(Forrest Gump\\)\n"
        "            Sally Field \\(Mrs. Gump\\)\n"
        "            Robin Wright \\(Jenny Curran\\)\n"
        "            Mykelti Williamson \\(Bubba Blue\\)\n"
        "        Directors:\n"
        "            Robert Zemeckis\n"
        "        Writers:\n"
        "            Winston Groom\n"
        "            Eric Roth\n"
        "        Media files: \\[\\]\n"
        "    Movie:\n"
        "        id: 3\n"
        "        title: Blade Runner\n"
        "        year: 1982\n"
        "        length: 117\n"
        "        Cast:\n"
        "            Harrison Ford \\(Rick Deckard\\)\n"
        "            Rutger Hauer \\(Roy Batty\\)\n"
        "            Sean Young \\(Rachael\\)\n"
        "        Directors:\n"
        "            Ridley Scott\n"
        "        Writers:\n"
        "            Hampton Fancher\n"
        "            David Webb Peoples\n"
        "            Philip K\\. Dick\n"
        "        Media files:\n"
        "            Media file:\n"
        "                id: 1\n"
        "                path: '.*res/db/poster\\.png'\n"
        "                description: 'Front cover'\n"
        "            Media file:\n"
        "                id: 2\n"
        "                path: '.*res/db/city\\.jpg'\n"
        "                description: 'Los Angeles'\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\(help for usage\\) > "  // list media 3
        "Media files:\n"
        "    Media file:\n"
        "        id: 1\n"
        "        path: '.*res/db/poster\\.png'\n"
        "        description: 'Front cover'\n"
        "    Media file:\n"
        "        id: 2\n"
        "        path: '.*res/db/city\\.jpg'\n"
        "        description: 'Los Angeles'\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\(help for usage\\) > "  // remove 2
        "Catalog:\n"
        "    Movie:\n"
        "        id: 1\n"
        "        title: The Matrix\n"
        "        year: 1999\n"
        "        length: 196\n"
        "        Cast:\n"
        "            Keanu Reeves \\(Neo\\)\n"
        "            Laurence Fishburne \\(Morpheus\\)\n"
        "            Carrie-Anne Moss \\(Trinity\\)\n"
        "            Hugo Weaving \\(Agent Smith\\)\n"
        "        Directors:\n"
        "            Lana Wachowski\n"
        "            Lilly Wachowski\n"
        "        Writers:\n"
        "            Lana Wachowski\n"
        "            Lilly Wachowski\n"
        "        Media files: \\[\\]\n"
        "    Movie:\n"
        "        id: 2\n"
        "        title: Forrest Gump\n"
        "        year: 1994\n"
        "        length: 202\n"
        "        Cast:\n"
        "            Tom Hanks \\(Forrest Gump\\)\n"
        "            Sally Field \\(Mrs. Gump\\)\n"
        "            Robin Wright \\(Jenny Curran\\)\n"
        "            Mykelti Williamson \\(Bubba Blue\\)\n"
        "        Directors:\n"
        "            Robert Zemeckis\n"
        "        Writers:\n"
        "            Winston Groom\n"
        "            Eric Roth\n"
        "        Media files: \\[\\]\n"
        "    Movie:\n"
        "        id: 3\n"
        "        title: Blade Runner\n"
        "        year: 1982\n"
        "        length: 117\n"
        "        Cast:\n"
        "            Harrison Ford \\(Rick Deckard\\)\n"
        "            Rutger Hauer \\(Roy Batty\\)\n"
        "            Sean Young \\(Rachael\\)\n"
        "        Directors:\n"
        "            Ridley Scott\n"
        "        Writers:\n"
        "            Hampton Fancher\n"
        "            David Webb Peoples\n"
        "            Philip K\\. Dick\n"
        "        Media files:\n"
        "            Media file:\n"
        "                id: 1\n"
        "                path: '.*res/db/poster\\.png'\n"
        "                description: 'Front cover'\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "\\(help for usage\\) > "  // list media 3
        "Media files:\n"
        "    Media file:\n"
        "        id: 1\n"
        "        path: '.*res/db/poster\\.png'\n"
        "        description: 'Front cover'\n"
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "(help for usage) > "  // quit
        "\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Are you sure you want to remove '.*/movies.db'\\? \\[y/n\\] \tOK\n"  // y
    ));
}
