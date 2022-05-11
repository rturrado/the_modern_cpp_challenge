#include "chapter_09_data_serialization/movies.h"
#include "chapter_10_archives_images_and_databases.h"
#include "chapter_10_archives_images_and_databases/sqlite_movies.h"

#include "rtc/sstream.h"  // get_unread
#include "rtc/string.h"  // to_lowercase

#include <filesystem>
#include <format>
#include <iostream>  // cin, cout
#include <map>
#include <optional>
#include <ranges>
#include <regex>
#include <sstream>  // istringstream, ostringstream
#include <stdexcept>  // runtime_error
#include <string>  // getline
#include <tuple>
#include <vector>

namespace fs = std::filesystem;


enum class command_t { add, help, list, quit, remove };
enum class subcommand_t { media, movie };

std::map<command_t, std::string> command_to_string{
    { command_t::add, "add" },
    { command_t::help, "help" },
    { command_t::list, "list" },
    { command_t::quit, "quit" },
    { command_t::remove, "remove" }
};
std::map<std::string, command_t> string_to_command{
    { "add", command_t::add },
    { "help", command_t::help },
    { "list", command_t::list },
    { "quit", command_t::quit},
    { "remove", command_t::remove }
};
std::map<subcommand_t, std::string> subcommmand_to_string{
    { subcommand_t::media, "media" },
    { subcommand_t::movie, "movie" }
};
std::map<std::string, subcommand_t> string_to_subcommand{
    { "media", subcommand_t::media },
    { "movie", subcommand_t::movie }
};
std::map<command_t, std::vector<subcommand_t>> command_to_subcommands{
    { command_t::list, { subcommand_t::media, subcommand_t::movie } }
};

struct CommandLineOptions
{
    int movie_id{};
    int media_id{};
    std::regex movie_title_regex{};
    fs::path media_file_path{};
    std::optional<std::string> media_file_description{};
};

struct CommandNotFoundError : public std::runtime_error
{
    CommandNotFoundError(const std::string& command) : std::runtime_error{ message_ + command } {}
private:
    static inline std::string message_{ "command not found: " };
};

struct SubcommandNotFoundError : public std::runtime_error
{
    SubcommandNotFoundError(const std::string& subcommand) : std::runtime_error{ message_ + subcommand } {}
private:
    static inline std::string message_{ "subcommand not found: " };
};

struct InvalidMediaIdError : public std::runtime_error
{
    InvalidMediaIdError(const std::string& media_id_str) : std::runtime_error{ message_ + media_id_str } {}
private:
    static inline std::string message_{ "invalid media ID: " };
};

struct InvalidMovieIdError : public std::runtime_error
{
    InvalidMovieIdError(const std::string& movie_id_str) : std::runtime_error{ message_ + movie_id_str } {}
private:
    static inline std::string message_{ "invalid movie ID: " };
};

struct InvalidSubcommandError : public std::runtime_error
{
    InvalidSubcommandError(const std::string& command_str, const std::string& subcommand_str) : std::runtime_error{ "" }
    {
        std::ostringstream oss{};
        oss << std::format("invalid subcommand '{}' for command '{}'", command_str, subcommand_str);
        message_ = oss.str();
    }
    virtual const char* what() const noexcept override { return message_.c_str(); }
private:
    std::string message_{};
};

void print_usage()
{
    std::cout << "Usage:\n";
    std::cout << "\tlist movie <movie_title_regex>\n";
    std::cout << "\tlist media <movie_id>\n";
    std::cout << "\tadd <movie_id>, <media_file_path>, [<media_file_description>]\n";
    std::cout << "\tremove <media_id>\n";
    std::cout << "\thelp\n";
    std::cout << "\tquit\n";
    std::cout << "Where:\n";
    std::cout << "\tmedia_file_description  Optional media file description.\n";
    std::cout << "\tmedia_file_path         File path pointing to a media file.\n";
    std::cout << "\tmedia_id                Media ID, as shown when listing a media file.\n";
    std::cout << "\tmovie_id                Movie ID, as shown when listing a movie.\n";
    std::cout << "\tmovie_title_regex       Regular expression for a movie title.\n";
    std::cout << "Examples:\n";
    std::cout << "\tlist movie .*The.*\n";
    std::cout << "\tlist media 4\n";
    std::cout << "\tadd 4, ./res/db/BladeRunner.jpg, Front cover\n";
    std::cout << "\tremove 0\n";
}

auto read_command_line()
{
    std::cout << "(help for usage) > ";
    std::string command_line{};
    std::getline(std::cin, command_line);
    return command_line;
}

void parse_command(std::istringstream& iss, command_t& command)
{
    std::string command_str{};
    iss >> command_str;
    command_str = rtc::string::to_lowercase(command_str);
    if (not string_to_command.contains(command_str)) {
        throw CommandNotFoundError{ command_str }; }
    command = string_to_command[command_str];
}

void parse_subcommand(std::istringstream& iss, const command_t& command, subcommand_t& subcommand)
{
    if (not command_to_subcommands.contains(command)) {  // this command has no subcommands
        return; }

    std::string subcommand_str{};
    iss >> subcommand_str;
    subcommand_str = rtc::string::to_lowercase(subcommand_str);
    if (not string_to_subcommand.contains(subcommand_str)) {  // this subcommand does not exist
        throw SubcommandNotFoundError{ subcommand_str }; }
    subcommand = string_to_subcommand[subcommand_str];
    
    auto& valid_subcommands{ command_to_subcommands[command] };
    if (std::ranges::find(valid_subcommands, subcommand) == std::cend(valid_subcommands)) {  // this command does not accept this subcommand
        throw InvalidSubcommandError{ command_to_string[command], subcommand_str }; }
}

void parse_media_id_option(std::istringstream& iss, CommandLineOptions& options)
{
    std::string media_id_str{};
    iss >> media_id_str;
    try { options.media_id = std::stoi(media_id_str); }
    catch (const std::exception&) { throw InvalidMediaIdError{ media_id_str }; }
}

void parse_movie_id_option(std::istringstream& iss, CommandLineOptions& options)
{
    std::string movie_id_str{};
    iss >> movie_id_str;
    try { options.movie_id = std::stoi(movie_id_str); }
    catch (const std::exception&) { throw InvalidMovieIdError{ movie_id_str }; }
}

void parse_movie_title_regex_option(std::istringstream& iss, CommandLineOptions& options)
{
    std::string movie_title_regex_str{};
    iss >> movie_title_regex_str;
    options.movie_title_regex = movie_title_regex_str;
}

void parse_add_options(std::istringstream& iss, CommandLineOptions& options) {
    std::string line{ rtc::sstream::get_unread(iss) };
    std::smatch matches{};
    const std::regex pattern{ R"(\s*([\d]+)\s*,\s*([^,]+)(?:,\s*(.*))?)" };
    if (std::regex_match(line, matches, pattern))
    {
        options.movie_id = std::stoi(matches[1].str());
        options.media_file_path = rtc::string::trim_right(matches[2].str());
        if (matches.size() == 4)
        {
            options.media_file_description = rtc::string::trim_right(matches[3].str());
        }
    }
}
void parse_list_media_options(std::istringstream& iss, CommandLineOptions& options) { parse_movie_id_option(iss, options); }
void parse_list_movie_options(std::istringstream& iss, CommandLineOptions& options) { parse_movie_title_regex_option(iss, options); }
void parse_remove_options(std::istringstream& iss, CommandLineOptions& options) { parse_media_id_option(iss, options); }

auto parse_command_line(std::string command_line)
{
    std::istringstream iss{ command_line };

    command_t command{}; parse_command(iss, command);
    subcommand_t subcommand{}; parse_subcommand(iss, command, subcommand);

    CommandLineOptions options{};
    switch (command)
    {
    case command_t::add: { parse_add_options(iss, options); break; }
    case command_t::help: break;
    case command_t::list:
    {
        switch (subcommand)
        {
        case subcommand_t::media: { parse_list_media_options(iss, options); break; }
        case subcommand_t::movie: { parse_list_movie_options(iss, options); break; }
        default: break;
        };
        break;
    }
    case command_t::quit: break;
    case command_t::remove: { parse_remove_options(iss, options); break; }
    default: break;
    }

    return std::tuple<command_t, subcommand_t, CommandLineOptions>{ command, subcommand, options };
}

void add_media(
    tmcppc::movies::sqlite_mcpp::database& movies_db,
    size_t movie_id,
    const fs::path& media_file_path,
    std::optional<std::string> media_file_description)
{
    if (not fs::exists(media_file_path)) {
        std::cout << std::format("Error: media file not found: {}\n", media_file_path.string());
        return; }

    try
    {
        auto media_file{ tmcppc::movies::MediaFile{ movie_id, media_file_path, media_file_description } };
        movies_db.insert_media_file(movie_id, media_file);
        std::cout << movies_db;
    }
    catch (const tmcppc::movies::sqlite_mcpp::MovieIdNotFoundError& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

void delete_media(tmcppc::movies::sqlite_mcpp::database& movies_db, size_t media_id)
{
    try
    {
        movies_db.delete_media_file(media_id);
        std::cout << movies_db;
    }
    catch (const tmcppc::movies::sqlite_mcpp::MediaFileIdNotFoundError& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

void list_media(const tmcppc::movies::sqlite_mcpp::database& movies_db, size_t movie_id)
{
    try
    {
        for (auto& media_file : movies_db.get_media_files(movie_id))
        {
            std::cout << media_file << "\n";
        }
    }
    catch (const tmcppc::movies::sqlite_mcpp::MovieIdNotFoundError& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

void list_movies(const tmcppc::movies::sqlite_mcpp::database& movies_db, const std::regex& pattern)
{
    for (auto& movie : movies_db.get_movies(pattern))
    {
        std::cout << movie << "\n";
    }
}

void execute_command(
    tmcppc::movies::sqlite_mcpp::database& movies_db,
    const command_t command,
    const subcommand_t subcommand,
    const CommandLineOptions& options)
{
    switch (command)
    {
    case command_t::add: { add_media(movies_db, options.movie_id, options.media_file_path, options.media_file_description); break; }
    case command_t::help: { print_usage(); break; }
    case command_t::list:
        switch (subcommand)
        {
        case subcommand_t::media: { list_media(movies_db, options.movie_id); break; }
        case subcommand_t::movie: { list_movies(movies_db, options.movie_title_regex); break; }
        default: break;
        };
        break;
    case command_t::remove: { delete_media(movies_db, options.media_id); break; }
    default: break;
    }
}

void menu(tmcppc::movies::sqlite_mcpp::database& movies_db)
{
    for (;;)
    {
        try
        {
            auto command_line{ read_command_line() };

            auto [command, subcommand, options] = parse_command_line(command_line);

            if (command == command_t::quit) { break; }

            execute_command(movies_db, command, subcommand, options);

            std::cout << "\n";
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: " << ex.what() << "\n\n";
        }
    }
}

// Handling movie images in an SQLite database
//
// Modify the program written for the previous problem to support adding media files (such as images, but also videos) to a movie.
// These files must be stored in a separate table in the database and have a unique numerical identifier, the movie identifier,
// a name (typically the filename), an optional description, and the actual media content, stored as a blob.
// The following is a diagram with the structure of the table that must be added to the existing database:
//
//   media
//   --------------------------
//   (key) rowid        integer
//         movieid      integer
//         name         text
//         description  text
//         content      blob
//
// The program written for this problem must support several commands:
//   - Listing all movies that match a search criterion (notably the title).
//   - Listing information about all existing media files for a movie.
//   - Adding a new media file for a movie.
//   - Deleting an existing media file.
void problem_87_main()
{
    const auto db_file_path{ fs::current_path() / "res" / "db" / "movies.db" };

    try
    {
        {
            auto sqlite_db{ tmcppc::movies::sqlite_mcpp::create_movies_database(db_file_path) };
            auto movies_db{ tmcppc::movies::sqlite_mcpp::database{ sqlite_db } };

            menu(movies_db);
        }

        std::cout << "\n";

        tmcppc::movies::sqlite_mcpp::remove_movies_database_file(db_file_path);
    }
    catch (const sqlite::sqlite_exception& ex)
    {
        std::cout << std::format("Error: code = {}, message = '{}', operation = '{}'\n",
            ex.get_code(), ex.what(), ex.get_sql());
    }
    catch (const std::exception& ex)
    {
        std::cout << "Error: " << ex.what() << "\n";
    }

    std::cout << "\n";
}
