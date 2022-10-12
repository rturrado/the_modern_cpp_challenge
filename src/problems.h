#pragma once

#include "chapter_01_math/problems.h"
#include "chapter_02_language_features/problems.h"
#include "chapter_03_strings_and_regular_expressions/problems.h"
#include "chapter_04_streams_and_filesystems/problems.h"
#include "chapter_05_date_and_time/problems.h"
#include "chapter_06_algorithms_and_data_structures/problems.h"
#include "chapter_07_concurrency/problems.h"
#include "chapter_08_design_patterns/problems.h"
#include "chapter_09_data_serialization/problems.h"
#include "chapter_10_archives_images_and_databases/problems.h"
#include "chapter_11_cryptography/problems.h"
#include "chapter_12_networking_and_services/problems.h"
#include "console.h"
#include "timer.h"

#include <chrono>
#include <functional>  // function, invoke
#include <vector>

#undef NDEBUG
#include <cassert>


class problems {
    using function_type = std::function<void()>;

public:
    static problems& get_instance() {
        static problems instance;
        return instance;
    }
    constexpr size_t size() {
        return data_.size();
    }
    void execute(size_t i) {
        assert((i > 0) && (i <= data_.size()));
        std::invoke(data_[i - 1]);
    }

private:
    problems() = default;

    std::vector<function_type> data_{
        // Math
        //
        []() { problem_1_main(std::cin, std::cout); },  // sum of naturals divisible by 3 or 5
        []() { problem_2_main(std::cin, std::cout); },  // greatest common divisor
        []() { problem_3_main(std::cin, std::cout); },  // least common multiple
        []() { problem_4_main(std::cin, std::cout); },  // largest prime smaller than given number
        []() { problem_5_main(std::cin, std::cout); },  // sexy prime pairs
        []() { problem_6_main(std::cin, std::cout); },  // abundant numbers
        []() { problem_7_main(std::cout); },  // amicable numbers
        []() { problem_8_main(std::cout); },  // armstrong numbers
        []() { problem_9_main(std::cin, std::cout); },  // prime factors
        []() { problem_10_main(std::cout); },  // gray code
        []() { problem_11_main(std::cin, std::cout); },  // converting numerical values to Roman
        []() { problem_12_main(std::cout); },  // largest Collatz sequence
        []() { problem_13_main(std::cout); },  // computing the value of Pi
        []() {
            using namespace tmcppc::system;

            problem_14_main(
                std::cin,
                std::cout,
                console{ std::make_unique<console_impl>() }
            ); },  // validating ISBNs

        // Language features
        //
        []() { problem_15_main(std::cin, std::cout); },  // IPv4 data type
        []() {
            using namespace tmcppc::system;

            problem_16_main(
                std::cin,
                std::cout,
                console{ std::make_unique<console_impl>() }
            ); },  // enumerating IPv4 addresses in a range
        []() { problem_17_main(std::cout); },  // 2D array
        []() { problem_18_main(std::cout); },  // variadic minimum function
        []() { problem_19_main(std::cout); },  // adding a range of values to a container
        []() { problem_20_main(std::cout); },  // contains any, all, or none from a range
        []() { problem_21_main(std::wcout); },  // system handle wrapper (Windows specific)
        []() { problem_22_main(std::cout); },  // temperature scales literals

        // Strings and regular expressions
        //
        []() { problem_23_main(std::cout); },  // binary to string conversion
        []() { problem_24_main(std::cout); },  // string to binary conversion
        []() { problem_25_main(std::cout); },  // capitalizing an article title
        []() { problem_26_main(std::cout); },  // joining strings with delimiter
        []() { problem_27_main(std::cout); },  // splitting a string into tokens
        []() { problem_28_main(std::cout); },  // longest palindromic substring
        []() { problem_29_main(std::cout); },  // license plate validation
        []() { problem_30_main(std::cout); },  // extracting URL parts
        []() { problem_31_main(std::cout); },  // transforming dates in strings

        // Streams and filesystems
        //
        []() { problem_32_main(std::cout); },  // Pascal's triangle
        []() { problem_33_main(std::cout); },  // tabular printing of a list of processes
        []() { problem_34_main(std::cout); },  // removing empty lines from a text file
        []() { problem_35_main(std::cout); },  // computing the size of a directory
        []() { problem_36_main(std::cout); },  // deleting files older than a given date
        []() { problem_37_main(std::cout); },  // regex find files in a directory
        []() { problem_38_main(std::cout); },  // temporary log files

        // Date and time
        //
        []() { problem_39_main(std::cout); },  // measuring function execution time
        []() { problem_40_main(std::cout); },  // number of days between two dates
        []() { problem_41_main(std::cout); },  // day of the week
        []() { problem_42_main(std::cout); },  // day and week of the year
        []() { problem_43_main(std::cout); },  // meeting time for multiple time zones
        []() { problem_44_main(std::cout); },  // monthly calendar

        // Algorithms and data structures
        //
        []() { problem_45_main(std::cout); },  // priority queue
        []() { problem_46_main(std::cout); },  // circular buffer
        []() { problem_47_main(std::cout); },  // double buffer
        []() { problem_48_main(std::cout); },  // most frequent element in a range
        []() { problem_49_main(std::cout); },  // text histogram
        []() { problem_50_main(std::cout); },  // filtering a list of phone numbers
        []() { problem_51_main(std::cout); },  // transforming a list of phone numbers
        []() { problem_52_main(std::cout); },  // generating all the permutations of a string
        []() { problem_53_main(std::cout); },  // average rating of movies
        []() { problem_54_main(std::cout); },  // pairwise algorithm
        []() { problem_55_main(std::cout); },  // zip algorithm
        []() { problem_56_main(std::cout); },  // select algorithm
        []() { problem_57_main(std::cout); },  // quicksort
        []() { problem_58_main(std::cout); },  // shortest path between two nodes
        []() { problem_59_main(std::cout); },  // Weasel program
        []() {
            using namespace std::chrono_literals;
            using namespace tmcppc::chrono;
            using namespace tmcppc::system;

            problem_60_main(
                std::cout,
                console{ std::make_unique<console_impl>() },
                timer{ std::make_unique<timer_impl>() },
                5s
            ); },  // game of life

        // Concurrency
        //
        []() { problem_61_main(std::cout); },  // parallel transform algorithm
        []() { problem_62_main(std::cout); },  // parallel minmax with threads
        []() { problem_63_main(std::cout); },  // parallel minmax with async
        []() { problem_64_main(std::cout); },  // parallel sort algorithm
        []() { problem_65_main(std::cout); },  // thread safe logging
        []() { problem_66_main(std::cin, std::cout); },  // customer service system

        // Design patterns
        //
        []() { problem_67_main(std::cout); },  // validating passwords
        []() { problem_68_main(std::cout); },  // generating random passwords
        []() { problem_69_main(std::cout); },  // generating social security numbers
        []() { problem_70_main(std::cout); },  // approval system
        []() { problem_71_main(std::cout); },  // observable vector container
        []() { problem_72_main(std::cout); },  // computing order price with discounts

        // Data serialization
        //
        []() { problem_73_main(std::cout); },  // XML serialization
        []() { problem_74_main(std::cout); },  // using XPath
        []() { problem_75_main(std::cout); },  // JSON serialization
        []() { problem_76_main(std::cout); },  // JSON deserialization
        []() { problem_77_main(std::cout); },  // printing a list of movies to a PDF
        []() { problem_78_main(std::cout); },  // creating a PDF from a collection of images

        // Archives, images, and databases
        //
        []() { problem_79_main(std::cout); },  // finding files in a ZIP archive
        []() { problem_80_main(std::cin, std::cout); },  // ZIP compression
        []() { problem_81_main(std::cin, std::cout); },  // zip compression with password
        []() { problem_82_main(std::cout); },  // national flag PNG
        []() { problem_83_main(std::cout); },  // verification text PNG
        []() { problem_84_main(std::cout); },  // EAN-13 barcode generator
        []() { problem_85_main(std::cin, std::cout); },  // reading from an SQLite database
        []() { problem_86_main(std::cin, std::cout); },  // inserting into an SQLite database
        []() { problem_87_main(std::cin, std::cout); },  // handling images in an SQLite database

        // Cryptography
        //
        []() { problem_88_main(std::cout); },  // Caesar cipher
        []() { problem_89_main(std::cout); },  // Vigenere cipher
        []() { problem_90_main(std::cout); },  // Base64 encoding
        []() { problem_91_main(std::cin, std::cout); },  // validating user credentials
        []() { problem_92_main(std::cout); },  // computing file hashes
        []() { problem_93_main(std::cout); },  // AES encryption
        []() { problem_94_main(std::cout); },  // file signing

        // Networking and services
        //
        []() { problem_95_main(std::cout); },  // finding the IP address of a host
        []() { problem_96_main(std::cin, std::cout); },  // Fizz-Buzz client server application
        []() { problem_97_main(std::cout); },  // Bitcoin exchange rates
        []() { problem_98_main(std::cin, std::cout); },  // fetching emails using IMAP
        []() { problem_99_main(std::cin, std::cout); },  // translating text
        []() { problem_100_main(std::cin, std::cout); }  // detecting faces in a picture
    };
};
