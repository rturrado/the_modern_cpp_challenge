#pragma once

#include "../movies.h"

#include <chrono>


namespace tmcppc::movies {
    namespace samples {
        namespace ch = std::chrono;

        // Role
        static inline const tmcppc::movies::role role{ "Tom Hanks", "Forrest Gump" };
        // Cast
        static inline const tmcppc::movies::cast cast{ {
            role,  // Tom Hanks, Forrest Gump
            {.star = "Sally Field", .name = "Mrs. Gump" },
            {.star = "Robin Wright", .name = "Jenny Curran" },
            {.star = "Mykelti Williamson", .name = "Bubba Blue" }
        } };

        // Director
        static inline const tmcppc::movies::director director{ "Robert Zemeckis" };
        // Directors
        static inline const tmcppc::movies::directors directors{ {
            director  // Robert Zemeckis
        } };

        // Writer
        static inline const tmcppc::movies::writer writer{ "Winston Groom" };
        // Writers
        static inline const tmcppc::movies::writers writers{ {
            writer,  // Winston Groom
            { "Eric Roth" }
        } };

        // Media file
        static inline const tmcppc::movies::media_file media_file_without_description{ 1, "./res/db/poster.png" };
        static inline const tmcppc::movies::media_file media_file{ 1, "./res/db/poster.png", "Front cover" };
        // Media files
        static inline const tmcppc::movies::media_files media_files{ {
            media_file,  // 1, poster.png, Front cover
            { 2, "./res/db/city.jpg", "Los Angeles" }
        } };

        // Movie
        static inline const tmcppc::movies::movie movie{
            .id = 9871,
            .title = "Forrest Gump",
            .year = ch::year{ 1994 },
            .length = 202,
            .cast = cast,
            .directors = directors,
            .writers = writers
        };
        // Movie with default ID
        static inline const tmcppc::movies::movie movie_with_default_id{
            .id = 0,
            .title = "Forrest Gump",
            .year = ch::year{ 1994 },
            .length = 202,
            .cast = cast,
            .directors = directors,
            .writers = writers
        };
        // Movie with default ID
        static inline const tmcppc::movies::movie movie_with_id_initialized_after_database_insertion{
            .id = 2,
            .title = "Forrest Gump",
            .year = ch::year{ 1994 },
            .length = 202,
            .cast = cast,
            .directors = directors,
            .writers = writers
        };

        // Catalog
        static inline const tmcppc::movies::catalog catalog{ {
            {
                .id = 11001,
                .title = "The Matrix",
                .year = ch::year{ 1999 },
                .length = 196,
                .cast = tmcppc::movies::cast{ {
                    {.star = "Keanu Reeves", .name = "Neo" },
                    {.star = "Laurence Fishburne", .name = "Morpheus" },
                    {.star = "Carrie-Anne Moss", .name = "Trinity" },
                    {.star = "Hugo Weaving", .name = "Agent Smith" }
                } },
                .directors = tmcppc::movies::directors{ {
                    {.name = "Lana Wachowski" },
                    {.name = "Lilly Wachowski" }
                } },
                .writers = tmcppc::movies::writers{ {
                    {.name = "Lana Wachowski" },
                    {.name = "Lilly Wachowski" }
                } }
            },
            movie  // Forrest Gump
        } };
        static inline const tmcppc::movies::catalog catalog_of_50_movies{ {
            { 1, "The Matrix", ch::year{ 1999 }, 136 },
            { 2, "Forrest Gump", ch::year{ 1994 }, 142 },
            { 3, "The Truman Show", ch::year{ 1998 }, 103 },
            { 4, "The Pursuit of Happyness", ch::year{ 2006 }, 117 },
            { 5, "Fight Club", ch::year{ 1999 }, 139 },
            { 6, "Inglourious Basterds", ch::year{ 2009 }, 153 },
            { 7, "The Dark Knight Rises", ch::year{ 2012 }, 164 },
            { 8, "The Dark Knight", ch::year{ 2008 }, 152 },
            { 9, "Pulp Fiction", ch::year{ 1994 }, 154 },
            { 10, "Inception", ch::year{ 2010 }, 148 },
            { 11, "The Shawshank Redemption", ch::year{ 1994 }, 142 },
            { 12, "The Silence of the Lambs", ch::year{ 1991 }, 118 },
            { 13, "Philadelphia", ch::year{ 1993 }, 125 },
            { 14, "One Flew Over the Cuckoo's Nest", ch::year{ 1975 }, 80 },
            { 15, "Memento", ch::year{ 2000 }, 113 },
            { 16, "Trainspotting", ch::year{ 1996 }, 94 },
            { 17, "Fargo", ch::year{ 1998 }, 98 },
            { 18, "Reservoir Dogs", ch::year{ 1992 }, 99 },
            { 19, "The Departed", ch::year{ 2006 }, 151 },
            { 20, "Se7en", ch::year{ 1995 }, 127 },
            { 21, "American History X", ch::year{ 1998 }, 119 },
            { 22, "Silver Linings Playbook", ch::year{ 2012 }, 122 },
            { 23, "2001: A Space Odyssey", ch::year{ 1968 }, 149 },
            { 24, "Monty Python and the Holy Grail", ch::year{ 1975 }, 91 },
            { 25, "Life of Brian", ch::year{ 1979 }, 94 },
            { 26, "Children of Men", ch::year{ 2006 }, 109 },
            { 27, "Sin City", ch::year{ 2005 }, 124 },
            { 28, "L.A. Confidential", ch::year{ 1997 }, 138 },
            { 29, "Shutter Island", ch::year{ 2010 }, 138 },
            { 30, "The Ten Commandments", ch::year{ 1956 }, 220 },
            { 31, "Interstellar", ch::year{ 2014 }, 169 },
            { 32, "The Godfather", ch::year{ 1972 }, 175 },
            { 33, "The Godfather II", ch::year{ 1974 }, 200 },
            { 34, "The Dark Knight", ch::year{ 2008 }, 152 },
            { 35, "Pulp Fiction", ch::year{ 1994 }, 154 },
            { 36, "The Good, The Bad, and The Ugly", ch::year{ 1966 }, 161 },
            { 37, "Schindler's List", ch::year{ 1993 }, 195 },
            { 38, "12 Angry Men", ch::year{ 1957 }, 96 },
            { 39, "The Lord of the Rings: The Fellowship of the Ring", ch::year{ 2001 }, 178 },
            { 40, "The Lord of the Rings: The Two Towers", ch::year{ 2002 }, 179 },
            { 41, "The Lord of the Rings: The Return of the King", ch::year{ 2003 }, 201 },
            { 42, "Star Wars: Episode IV - A New Hope", ch::year{ 1977 }, 121 },
            { 43, "Star Wars: Episode V - The Empire Strikes Back", ch::year{ 1980 }, 124 },
            { 44, "Goodfellas", ch::year{ 1990 }, 146 },
            { 45, "The Seven Samurai", ch::year{ 1954 }, 207 },
            { 46, "City of God", ch::year{ 2002 }, 130 },
            { 47, "The Usual Suspects", ch::year{ 1995 }, 106 },
            { 48, "Once Upon a Time in the West", ch::year{ 1968 }, 175 },
            { 49, "Casablanca", ch::year{ 1942 }, 102 },
            { 50, "American History X", ch::year{ 1998 }, 119 }
        } };
    };  // namespace samples
}  // namespace tmcppc::movies
