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

#include <cassert>  // assert
#include <functional>  // function, invoke
#include <vector>


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
    problems() {};

    std::vector<function_type> data_{
        // Math
        //
        []() { problem_1_main(); },  // sum of naturals divisible by 3 or 5
        []() { problem_2_main(); },  // greatest common divisor
        []() { problem_3_main(); },  // least common multiple
        []() { problem_4_main(); },  // largest prime smaller than given number
        []() { problem_5_main(); },  // sexy prime pairs
        []() { problem_6_main(); },  // abundant numbers
        []() { problem_7_main(); },  // amicable numbers
        []() { problem_8_main(); },  // armstrong numbers
        []() { problem_9_main(); },  // prime factors
        []() { problem_10_main(); },  // gray code
        []() { problem_11_main(); },  // converting numerical values to Roman
        []() { problem_12_main(); },  // largest Collatz sequence
        []() { problem_13_main(); },  // computing the value of Pi
        []() { problem_14_main(); },  // validating ISBNs

        // Language features
        //
        []() { problem_15_main(); },  // IPv4 data type
        []() { problem_16_main(); },  // enumerating IPv4 addresses in a range
        []() { problem_17_main(); },  // 2D array
        []() { problem_18_main(); },  // variadic minimum function
        []() { problem_19_main(); },  // adding a range of values to a container
        []() { problem_20_main(); },  // contains any, all, or none from a range
        []() { problem_21_main(); },  // system handle wrapper (Windows specific)
        []() { problem_22_main(); },  // temperature scales literals

        // Strings and regular expressions
        //
        []() { problem_23_main(); },  // binary to string conversion
        []() { problem_24_main(); },  // string to binary conversion
        []() { problem_25_main(); },  // capitalizing an article title
        []() { problem_26_main(); },  // joining strings with delimiter
        []() { problem_27_main(); },  // splitting a string into tokens
        []() { problem_28_main(); },  // longest palindromic substring
        []() { problem_29_main(); },  // license plate validation
        []() { problem_30_main(); },  // extracting URL parts
        []() { problem_31_main(); },  // transforming dates in strings

        // Streams and filesystems
        //
        []() { problem_32_main(); },  // Pascal's triangle
        []() { problem_33_main(); },  // tabular printing of a list of processes
        []() { problem_34_main(); },  // removing empty lines from a text file
        []() { problem_35_main(); },  // computing the size of a directory
        []() { problem_36_main(); },  // deleting files older than a given date
        []() { problem_37_main(); },  // regex find files in a directory
        []() { problem_38_main(); },  // temporary log files

        // Date and time
        //
        []() { problem_39_main(); },  // measuring function execution time
        []() { problem_40_main(); },  // number of days between two dates
        []() { problem_41_main(); },  // day of the week
        []() { problem_42_main(); },  // day and week of the year
        []() { problem_43_main(); },  // meeting time for multiple time zones
        []() { problem_44_main(); },  // monthly calendar

        // Algorithms and data structures
        //
        []() { problem_45_main(); },  // priority queue
        []() { problem_46_main(); },  // circular buffer
        []() { problem_47_main(); },  // double buffer
        []() { problem_48_main(); },  // most frequent element in a range
        []() { problem_49_main(); },  // text histogram
        []() { problem_50_main(); },  // filtering a list of phone numbers
        []() { problem_51_main(); },  // transforming a list of phone numbers
        []() { problem_52_main(); },  // generating all the permutations of a string
        []() { problem_53_main(); },  // average rating of movies
        []() { problem_54_main(); },  // pairwise algorithm
        []() { problem_55_main(); },  // zip algorithm
        []() { problem_56_main(); },  // select algorithm
        []() { problem_57_main(); },  // quicksort
        []() { problem_58_main(); },  // shortest path between two nodes
        []() { problem_59_main(); },  // Weasel program
        []() { problem_60_main(); },  // game of life

        // Concurrency
        //
        []() { problem_61_main(); },  // parallel transform algorithm
        []() { problem_62_main(); },  // parallel minmax with threads
        []() { problem_63_main(); },  // parallel minmax with async
        []() { problem_64_main(); },  // parallel sort algorithm
        []() { problem_65_main(); },  // thread safe logging
        []() { problem_66_main(); },  // customer service system

        // Design patterns
        //
        []() { problem_67_main(); },  // validating passwords
        []() { problem_68_main(); },  // generating random passwords
        []() { problem_69_main(); },  // generating social security numbers
        []() { problem_70_main(); },  // approval system
        []() { problem_71_main(); },  // observable vector container
        []() { problem_72_main(); },  // computing order price with discounts

        // Data serialization
        //
        []() { problem_73_main(); },  // XML serialization
        []() { problem_74_main(); },  // using XPath
        []() { problem_75_main(); },  // JSON serialization
        []() { problem_76_main(); },  // JSON deserialization
        []() { problem_77_main(); },  // printing a list of movies to a PDF
        []() { problem_78_main(); },  // creating a PDF from a collection of images

        // Archives, images, and databases
        //
        []() { problem_79_main(); },  // finding files in a ZIP archive
        []() { problem_80_main(); },  // ZIP compression
        []() { problem_81_main(); },  // zip compression with password
        []() { problem_82_main(); },  // national flag PNG
        []() { problem_83_main(); },  // verification text PNG
        []() { problem_84_main(); },  // EAN-13 barcode generator
        []() { problem_85_main(); },  // reading from an SQLite database
        []() { problem_86_main(); },  // inserting into an SQLite database
        []() { problem_87_main(); },  // handling images in an SQLite database

        // Cryptography
        //
        []() { problem_88_main(); },  // Caesar cipher
        []() { problem_89_main(); },  // Vigenere cipher
        []() { problem_90_main(); },  // Base64 encoding
        []() { problem_91_main(); },  // validating user credentials
        []() { problem_92_main(); },  // computing file hashes
        []() { problem_93_main(); },  // AES encryption
        []() { problem_94_main(); },  // file signing

        // Networking and services
        //
        []() { problem_95_main(); },  // finding the IP address of a host
        []() { problem_96_main(); },  // Fizz-Buzz client server application
        []() { problem_97_main(); },  // Bitcoin exchange rates
        []() { problem_98_main(); },  // fetching emails using IMAP
        []() { problem_99_main(); },  // translating text
        []() { problem_100_main(); }  // detecting faces in a picture
    };
};
