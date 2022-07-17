#include "chapter_09_data_serialization/movies_samples.h"

#include <chrono>

using namespace std::chrono_literals;


namespace tmcppc::movies {
    // Role
    const role role_sample{ "Tom Hanks", "Forrest Gump" };


    // Cast
    const cast cast_sample{ {
        role_sample,
        { .star = "Sally Field", .name = "Mrs. Gump" },
        { .star = "Robin Wright", .name = "Jenny Curran" },
        { .star = "Mykelti Williamson", .name = "Bubba Blue" }
    } };


    // Director
    const director director_sample{ "Robert Zemeckis" };


    // Directors
    const directors directors_sample{ {
        director_sample
    } };


    // Writer
    const writer writer_sample{ "Winston Groom" };


    // Writers
    const writers writers_sample{ {
        writer_sample,
        { "Eric Roth" }
    } };


    // Media file
    const media_file media_file_without_description_sample{ 1, "./res/db/poster.png" };
    const media_file media_file_sample{ 1, "./res/db/poster.png", "Front cover" };


    // Media files
    const media_files media_files_sample{ {
        media_file_sample,
        { 2, "./res/db/city.jpg", "Los Angeles" }
    } };


    // Movie
    const movie movie_sample{
        .id = 9871,
        .title = "Forrest Gump",
        .year = 1994y,
        .length = 202,
        .cast = cast_sample,
        .directors = directors_sample,
        .writers = writers_sample
    };

    // Movie with default ID
    const movie movie_with_default_id_sample{
        .id = 0,
        .title = "Forrest Gump",
        .year = 1994y,
        .length = 202,
        .cast = cast_sample,
        .directors = directors_sample,
        .writers = writers_sample
    };

    // Movie with default ID
    const movie movie_with_id_initialized_after_database_insertion_sample{
        .id = 2,
        .title = "Forrest Gump",
        .year = 1994y,
        .length = 202,
        .cast = cast_sample,
        .directors = directors_sample,
        .writers = writers_sample
    };


    // Catalog
    const catalog catalog_sample{ {
        {
            .id = 11001,
            .title = "The Matrix",
            .year = 1999y,
            .length = 196,
            .cast = tmcppc::movies::cast{{
                { .star = "Keanu Reeves", .name = "Neo" },
                { .star = "Laurence Fishburne", .name = "Morpheus" },
                { .star = "Carrie-Anne Moss", .name = "Trinity" },
                { .star = "Hugo Weaving", .name = "Agent Smith" }
            }},
            .directors = directors{{
                { .name = "Lana Wachowski" },
                { .name = "Lilly Wachowski" }
            }},
            .writers = writers{{
                { .name = "Lana Wachowski" },
                { .name = "Lilly Wachowski" }
            }}
        },
        movie_sample
    } };

    const catalog catalog_of_2_movies{ {
        { 1, "The Matrix", 1999y, 136 },
        { 2, "Forrest Gump", 1994y, 142 }
    } };

    const catalog catalog_of_30_movies{ {
        { 1, "The Matrix", 1999y, 136 },
        { 2, "Forrest Gump", 1994y, 142 },
        { 3, "The Truman Show", 1998y, 103 },
        { 4, "The Pursuit of Happyness", 2006y, 117 },
        { 5, "Fight Club", 1999y, 139 },
        { 6, "Inglourious Basterds", 2009y, 153 },
        { 7, "The Dark Knight Rises", 2012y, 164 },
        { 8, "The Dark Knight", 2008y, 152 },
        { 9, "Pulp Fiction", 1994y, 154 },
        { 10, "Inception", 2010y, 148 },
        { 11, "The Shawshank Redemption", 1994y, 142 },
        { 12, "The Silence of the Lambs", 1991y, 118 },
        { 13, "Philadelphia", 1993y, 125 },
        { 14, "One Flew Over the Cuckoo's Nest", 1975y, 80 },
        { 15, "Memento", 2000y, 113 },
        { 16, "Trainspotting", 1996y, 94 },
        { 17, "Fargo", 1998y, 98 },
        { 18, "Reservoir Dogs", 1992y, 99 },
        { 19, "The Departed", 2006y, 151 },
        { 20, "Se7en", 1995y, 127 },
        { 21, "American History X", 1998y, 119 },
        { 22, "Silver Linings Playbook", 2012y, 122 },
        { 23, "2001: A Space Odyssey", 1968y, 149 },
        { 24, "Monty Python and the Holy Grail", 1975y, 91 },
        { 25, "Life of Brian", 1979y, 94 },
        { 26, "Children of Men", 2006y, 109 },
        { 27, "Sin City", 2005y, 124 },
        { 28, "L.A. Confidential", 1997y, 138 },
        { 29, "Shutter Island", 2010y, 138 },
        { 30, "The Ten Commandments", 1956y, 220 }
    } };

    const catalog catalog_of_50_movies{ {
        { 1, "The Matrix", 1999y, 136 },
        { 2, "Forrest Gump", 1994y, 142 },
        { 3, "The Truman Show", 1998y, 103 },
        { 4, "The Pursuit of Happyness", 2006y, 117 },
        { 5, "Fight Club", 1999y, 139 },
        { 6, "Inglourious Basterds", 2009y, 153 },
        { 7, "The Dark Knight Rises", 2012y, 164 },
        { 8, "The Dark Knight", 2008y, 152 },
        { 9, "Pulp Fiction", 1994y, 154 },
        { 10, "Inception", 2010y, 148 },
        { 11, "The Shawshank Redemption", 1994y, 142 },
        { 12, "The Silence of the Lambs", 1991y, 118 },
        { 13, "Philadelphia", 1993y, 125 },
        { 14, "One Flew Over the Cuckoo's Nest", 1975y, 80 },
        { 15, "Memento", 2000y, 113 },
        { 16, "Trainspotting", 1996y, 94 },
        { 17, "Fargo", 1998y, 98 },
        { 18, "Reservoir Dogs", 1992y, 99 },
        { 19, "The Departed", 2006y, 151 },
        { 20, "Se7en", 1995y, 127 },
        { 21, "American History X", 1998y, 119 },
        { 22, "Silver Linings Playbook", 2012y, 122 },
        { 23, "2001: A Space Odyssey", 1968y, 149 },
        { 24, "Monty Python and the Holy Grail", 1975y, 91 },
        { 25, "Life of Brian", 1979y, 94 },
        { 26, "Children of Men", 2006y, 109 },
        { 27, "Sin City", 2005y, 124 },
        { 28, "L.A. Confidential", 1997y, 138 },
        { 29, "Shutter Island", 2010y, 138 },
        { 30, "The Ten Commandments", 1956y, 220 },
        { 31, "Interstellar", 2014y, 169 },
        { 32, "The Godfather", 1972y, 175 },
        { 33, "The Godfather II", 1974y, 200 },
        { 34, "The Dark Knight", 2008y, 152 },
        { 35, "Pulp Fiction", 1994y, 154 },
        { 36, "The Good, The Bad, and The Ugly", 1966y, 161 },
        { 37, "Schindler's List", 1993y, 195 },
        { 38, "12 Angry Men", 1957y, 96 },
        { 39, "The Lord of the Rings: The Fellowship of the Ring", 2001y, 178 },
        { 40, "The Lord of the Rings: The Two Towers", 2002y, 179 },
        { 41, "The Lord of the Rings: The Return of the King", 2003y, 201 },
        { 42, "Star Wars: Episode IV - A New Hope", 1977y, 121 },
        { 43, "Star Wars: Episode V - The Empire Strikes Back", 1980y, 124 },
        { 44, "Goodfellas", 1990y, 146 },
        { 45, "The Seven Samurai", 1954y, 207 },
        { 46, "City of God", 2002y, 130 },
        { 47, "The Usual Suspects", 1995y, 106 },
        { 48, "Once Upon a Time in the West", 1968y, 175 },
        { 49, "Casablanca", 1942y, 102 },
        { 50, "American History X", 1998y, 119 }
    } };
}  // namespace tmcppc::movies
