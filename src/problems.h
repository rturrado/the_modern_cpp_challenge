#pragma once

#include "chapter_01_math/problems.h"
/*
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
*/

#include <cassert>  // assert
#include <functional>  // function, invoke
#include <vector>


class problems
{
    using function_type = std::function<void()>;

public:
    static problems& get_instance()
    {
        static problems instance;
        return instance;
    }
    constexpr size_t size()
    {
        return data_.size();
    }
    void execute(size_t i)
    {
        assert((i > 0) && (i <= data_.size()));
        std::invoke(data_[i - 1]);
    }

private:
    problems() {};

    std::vector<function_type> data_{
        // Math
        //
        problem_1_main,  // sum of naturals divisible by 3 and 5
        problem_2_main,  // greatest common divisor
        problem_3_main,  // least common multiple
        problem_4_main,  // largest prime smaller than given number
        problem_5_main,  // sexy prime pairs
        problem_6_main,  // abundant numbers
        problem_7_main,  // amicable numbers
        problem_8_main,  // armstrong numbers
        problem_9_main,  // prime factors
        problem_10_main,  // gray code
        problem_11_main,  // converting numerical values to Roman
        problem_12_main,  // largest Collatz sequence
        problem_13_main,  // computing the value of Pi
        problem_14_main,  // validating ISBNs

/*
        // Language features
        //
        problem_15_main,  
        problem_16_main,
        problem_17_main,
        problem_18_main,
        problem_19_main,
        problem_20_main,
        problem_21_main,
        problem_22_main,

        // Strings and regular expressions
        //
        problem_23_main,
        problem_24_main,
        problem_25_main,
        problem_26_main,
        problem_27_main,
        problem_28_main,
        problem_29_main,
        problem_30_main,
        problem_31_main,

        // Streams and filesystems
        //
        problem_32_main,
        problem_33_main,
        problem_34_main,
        problem_35_main,
        problem_36_main,
        problem_37_main,
        problem_38_main,

        // Date and time
        //
        problem_39_main,
        problem_40_main,
        problem_41_main,
        problem_42_main,
        problem_43_main,
        problem_44_main,

        // Algorithms and data structures
        //
        problem_45_main,
        problem_46_main,
        problem_47_main,
        problem_48_main,
        problem_49_main,
        problem_50_main,
        problem_51_main,
        problem_52_main,
        problem_53_main,
        problem_54_main,
        problem_55_main,
        problem_56_main,
        problem_57_main,
        problem_58_main,
        problem_59_main,
        problem_60_main,

        // Concurrency
        //
        problem_61_main,
        problem_62_main,
        problem_63_main,
        problem_64_main,
        problem_65_main,
        problem_66_main,

        // Design patterns
        //
        problem_67_main,
        problem_68_main,
        problem_69_main,
        problem_70_main,
        problem_71_main,
        problem_72_main,

        // Data serialization
        //
        problem_73_main,
        problem_74_main,
        problem_75_main,
        problem_76_main,
        problem_77_main,
        problem_78_main,

        // Archives, images, and databases
        //
        problem_79_main,
        problem_80_main,
        problem_81_main,
        problem_82_main,
        problem_83_main,
        problem_84_main,
        problem_85_main,
        problem_86_main,
        problem_87_main,

        // Cryptography
        //
        problem_88_main,
        problem_89_main,
        problem_90_main,
        problem_91_main,
        problem_92_main,
        problem_93_main,
        problem_94_main,

        // Networking and services
        //
        problem_95_main,
        problem_96_main,
        problem_97_main,
        problem_98_main,
        problem_99_main,
        problem_100_main
*/
    };
};
