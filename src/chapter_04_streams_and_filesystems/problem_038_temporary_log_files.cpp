#include "chapter_04_streams_and_filesystems/problem_038_temporary_log_files.h"

#include <boost/uuid/random_generator.hpp>  // random_generator
#include <boost/uuid/uuid_io.hpp>  // to_string
#include <exception>
#include <filesystem>
#include <fstream>  // ofstream
#include <ios>  // ios_base
#include <iostream>  // cout
#include <stdexcept>  // runtime_error
#include <string>
#include <string_view>


namespace logger
{
    namespace
    {
        namespace fs = std::filesystem;
        namespace uuids = boost::uuids;
    }

    struct CouldNotOpenFile : public std::runtime_error { CouldNotOpenFile(std::string_view error) : std::runtime_error(error.data()) {} };

    class Logger
    {
    public:
        Logger()
            : file_path_{ fs::temp_directory_path() / fs::path{ uuids::to_string(uuids::random_generator{}()) + ".log" } }
        { open_file(); }

        [[nodiscard]] std::string get_file_path() const noexcept { return file_path_.string(); }

        void log(std::string_view text) noexcept { file_ << text.data(); }

        void move_file(std::string_view new_file_path)
        {
            if (new_file_path != file_path_.string())
            {
                close_file();  // close current file stream
                fs::rename(file_path_, new_file_path);  // move current file; this operation may throw
                file_path_ = new_file_path;
                moved = true;
                reopen_file();  // reopen moved file
            }
        }

        ~Logger() noexcept { close_file(); if (not moved) { remove_file(); } }

    private:
        fs::path file_path_{};
        std::ofstream file_{};
        bool moved{ false };

        void open_file(std::ios_base::openmode mode = std::ios_base::out)
        {
            file_.open(file_path_.string(), mode);
            if (!file_)
            {
                throw CouldNotOpenFile{ file_path_.string() };
            }
        }
        void reopen_file() { open_file(std::ios_base::app); }
        void close_file() { file_.close(); }
        void remove_file() { fs::remove(file_path_); }
    };
}


// Temporary log files
//
// Create a logging class that writes text messages to a discardable text file.
// The text file should have a unique name and must be located in a temporary directory.
// Unless specified otherwise, this log file should be deleted when the instance of the class is destroyed.
// However, it should be possible to retain the log file by moving it to a permanent location.
void problem_38_main()
{
    using namespace logger;

    try
    {
        std::cout << "Creating logger_1 and logger_2 instances...\n";
        Logger logger_1{};
        Logger logger_2{};

        std::cout << "Writing out to logger_1 and logger_2...\n";
        logger_1.log("R u awake? Want 2 chat?\n");
        logger_2.log("O Rom. Where4 art thou?\n");
        logger_1.log("Outside yr window.\n");
        logger_2.log("Stalker! J/K.\n");
        logger_1.log("Had 2—feeln’ romantc.\n");
        logger_2.log("B careful. My family h8 u.\n");
        logger_1.log("I no. What about u ?\n");
        logger_2.log("'M up for marriage if u r. Is tht a bit fwd?\n");
        logger_1.log("No. Yes. No. Oh, dsnt mat-r. 2moro @ 9?\n");
        logger_2.log("Luv U xxxx\n");

        std::string_view log_1_new_location{ "C:\\Users\\Roberto\\Desktop\\log_1.txt" };
        std::cout << "Moving logger_1 from " << logger_1.get_file_path() << " to " << log_1_new_location << "\n";
        logger_1.move_file(log_1_new_location);

        std::cout << "Writing out something else to logger_1...\n";
        logger_1.log("CU then xxxx\n");

        std::string_view log_1_second_new_location{ "C:\\Users\\Roberto\\Desktop\\log_1-new.txt" };
        std::cout << "Moving logger_1 from " << log_1_new_location << " to " << log_1_second_new_location << "\n";
        logger_1.move_file(log_1_second_new_location);

        std::cout << "Asking for logger_1 location: " << logger_1.get_file_path() << "\n";
    }
    catch (const std::exception& err)
    {
        std::cout << "Error: " << err.what() << "\n";
    }

    std::cout << "\n";
}
