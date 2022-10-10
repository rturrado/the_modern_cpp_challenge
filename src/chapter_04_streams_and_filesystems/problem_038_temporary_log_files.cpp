#include "chapter_04_streams_and_filesystems/logger.h"
#include "chapter_04_streams_and_filesystems/problem_038_temporary_log_files.h"

#include <exception>
#include <fmt/ostream.h>
#include <filesystem>
#include <iostream>  // cout
#include <string_view>


// Temporary log files
//
// Create a logging class that writes text messages to a discardable text file.
// The text file should have a unique name and must be located in a temporary directory.
// Unless specified otherwise, this log file should be deleted when the instance of the class is destroyed.
// However, it should be possible to retain the log file by moving it to a permanent location.
void problem_38_main(std::ostream& os) {
    using namespace tmcppc::logging::v1;

    try {
        auto trace_log = [&os](logger& logger, std::string_view sv) {
            logger.log(sv);
            fmt::print(os, "\t{}", sv);
        };

        fmt::print(os, "Creating logger_1 and logger_2 instances...\n");
        logger logger_1{};
        logger logger_2{};

        fmt::print(os, "Writing out to logger_1 and logger_2...\n");
        trace_log(logger_1, "R u awake? Want 2 chat?\n");
        trace_log(logger_2, "O Rom. Where4 art thou?\n");
        trace_log(logger_1, "Outside yr window.\n");
        trace_log(logger_2, "Stalker! J/K.\n");
        trace_log(logger_1, "Had 2-feeln' romantc.\n");
        trace_log(logger_2, "B careful. My family h8 u.\n");
        trace_log(logger_1, "I no. What about u?\n");
        trace_log(logger_2, "'M up for marriage if u r. Is tht a bit fwd?\n");
        trace_log(logger_1, "No. Yes. No. Oh, dsnt mat-r. 2moro @ 9?\n");
        trace_log(logger_2, "Luv U xxxx\n");

        const auto log_1_new_location{ std::filesystem::temp_directory_path() / "log_1.txt" };
        fmt::print(os, "Moving logger_1 from '{}' to '{}'\n", logger_1.get_file_path(), log_1_new_location.generic_string());
        logger_1.move_file(log_1_new_location);

        fmt::print(os, "Writing out something else to logger_1...\n");
        trace_log(logger_1, "CU then xxxx\n");

        const auto log_1_second_new_location{ std::filesystem::temp_directory_path() / "log_1-new.txt" };
        fmt::print(os, "Moving logger_1 from '{}' to '{}'\n",
            log_1_new_location.generic_string(), log_1_second_new_location.generic_string());
        logger_1.move_file(log_1_second_new_location);

        fmt::print(os, "Asking for logger_1 location: '{}'\n", logger_1.get_file_path());
    } catch (const std::exception& err) {
        fmt::print(os, "Error: {}\n", err.what());
    }

    fmt::print(os, "\n");
}
