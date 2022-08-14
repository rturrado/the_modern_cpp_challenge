#include "chapter_10_archives_images_and_databases/problem_086_inserting_into_an_sqlite_db.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>  // istringstream, ostringstream


TEST(problem_86_main, DISABLED_output) {
    std::istringstream iss{
        "1\n"  // 1 for Console
        "Fight Club\n"  // title
        "1990\n"  // year
        "139\n"  // length (in minutes)
        "Brad Pitt\n"  // star name 1
        "Tyler Durden\n"  // role name 1
        "Edward Norton\n"  // star name 2
        "Narrator\n"  // role name 2
        "Meat Loaf\n"  // star name 3
        "Robert Paulsen\n"  // role name 3
        "quit\n"  // exiting cast
        "David Fincher\n"  // director name
        "quit\n"  // exiting directors
        "Chuck Palahniuk\n"  // writer name 1
        "Jim Uhls\n"  // writer name 2
        "quit\n"  // exiting writers
        "y\n"  // yes, I want to add this movie to the list
        "2\n"  // 2 for File
        "n\n"  // no, I don't want to add Fight Club again to the list
        "y\n"  // yes, I want to add Blade Runner to the list
        "q\n"  // quit
        "y\n"  // yes, I want to remove .*/movies.db
    };
    std::ostringstream oss{};
    problem_86_main(iss, oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Choose method for adding a new movie (1 - Console, 2 - File, q - Quit): \tOK\n"  // 1
        "Please enter the movie data:\n"
        "Title?\n"  // Fight Club
        "Year?\n"
        "Please enter a number (>= 1900): \tOK\n"  // 1990
        "Length (in minutes)?\n"
        "Please enter a number (>= 0): \tOK\n"  // 139
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Cast? ('quit' to end the list)\n"
        "Please enter a star's full name (e.g. Tom Hanks): "  //Brad Ptt
        "Please enter a role name (e.g. Forrest Gump): "  // Tyler Durden
        "Please enter a star's full name (e.g. Tom Hanks): "  // Edward Norton
        "Please enter a role name (e.g. Forrest Gump): "  // Narrator
        "Please enter a star's full name (e.g. Tom Hanks): "  // Meat Loaf
        "Please enter a role name (e.g. Forrest Gump): "  // Robert Paulsen
        "Please enter a star's full name (e.g. Tom Hanks): "  // quit
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Directors? ('quit' to end the list)\n"
        "Please enter a director's full name (e.g. Robert Zemeckis): "  // David Fincher
        "Please enter a director's full name (e.g. Robert Zemeckis): "  // quit
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Writers? ('quit' to end the list)\n"
        "Please enter a writer's full name (e.g. Eric Roth): "  // Chuck Palahniuk
        "Please enter a writer's full name (e.g. Eric Roth): "  // Jim Uhls
        "Please enter a writer's full name (e.g. Eric Roth): "  // quit
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Movie:\n"
        "    title: Fight Club\n"
        "    year: 1990\n"
        "    length: 139\n"
        "    Cast:\n"
        "        Brad Pitt (Tyler Durden)\n"
        "        Edward Norton (Narrator)\n"
        "        Meat Loaf (Robert Paulsen)\n"
        "    Directors:\n"
        "        David Fincher\n"
        "    Writers:\n"
        "        Chuck Palahniuk\n"
        "        Jim Uhls\n"
        "    Media files: []\n"
        "\n"
        "Are you sure you want to add this movie to the movies database? [y/n] "  // y
        "\tOK\n"
        "Choose method for adding a new movie (1 - Console, 2 - File, q - Quit): "  // 2
        "\tOK\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::ContainsRegex(
        "Adding movies from .*/res/db/new_movies.txt\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Movie:\n"
        "    title: Fight Club\n"
        "    year: 1990\n"
        "    length: 139\n"
        "    Cast:\n"
        "        Brad Pitt (Tyler Durden)\n"
        "        Edward Norton (Narrator)\n"
        "        Meat Loaf (Robert Paulsen)\n"
        "    Directors:\n"
        "        David Fincher\n"
        "    Writers:\n"
        "        Chuck Palahniuk\n"
        "        Jim Uhls\n"
        "    Media files: []\n"
        "\n"
        "Are you sure you want to add this movie to the movies database? [y/n] "  // n
        "\tOK\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Movie:\n"
        "    title: Blade Runner\n"
        "    year: 1982\n"
        "    length: 117\n"
        "    Cast:\n"
        "        Harrison Ford (Rick Deckard)\n"
        "        Rutger Hauer (Roy Batty)\n"
        "        Sean Young (Rachael)\n"
        "    Directors:\n"
        "        Ridley Scott\n"
        "    Writers:\n"
        "        Hampton Fancher\n"
        "        David Webb Peoples\n"
        "        Philip K. Dick\n"
        "    Media files: []\n"
        "\n"
        "Are you sure you want to add this movie to the movies database? [y/n] "  // y
        "\tOK\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Choose method for adding a new movie (1 - Console, 2 - File, q - Quit): "  // q
        "\tOK\n"
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
        "    Movie:\n"
        "        id: 3\n"
        "        title: Fight Club\n"
        "        year: 1990\n"
        "        length: 139\n"
        "        Cast:\n"
        "            Brad Pitt (Tyler Durden)\n"
        "            Edward Norton (Narrator)\n"
        "            Meat Loaf (Robert Paulsen)\n"
        "        Directors:\n"
        "            David Fincher\n"
        "        Writers:\n"
        "            Chuck Palahniuk\n"
        "            Jim Uhls\n"
        "        Media files: []\n"
        "    Movie:\n"
        "        id: 4\n"
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
        "Are you sure you want to remove '.*/movies.db'\\? \\[y/n\\] "  // y
        "\tOK\n\n"
    ));
    EXPECT_THAT(oss.str(), ::testing::Not(::testing::EndsWith("\n\n\n")));
}
