//  Copyright (c) 2017 Taeguk Kwon
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "inplace_merge_tests.hpp"
#include "test_utils.hpp"

////////////////////////////////////////////////////////////////////////////
void inplace_merge_test()
{
    std::cout << "--- inplace_merge_test ---" << std::endl;
    test_inplace_merge<std::random_access_iterator_tag>();
    //test_inplace_merge<std::bidirectional_iterator_tag>();
}

void inplace_merge_exception_test()
{
    std::cout << "--- inplace_merge_exception_test ---" << std::endl;
    test_inplace_merge_exception<std::random_access_iterator_tag>();
    //test_inplace_merge_exception<std::bidirectional_iterator_tag>();
}

void inplace_merge_bad_alloc_test()
{
    std::cout << "--- inplace_merge_bad_alloc_test ---" << std::endl;
    test_inplace_merge_bad_alloc<std::random_access_iterator_tag>();
    //test_inplace_merge_bad_alloc<std::bidirectional_iterator_tag>();
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(boost::program_options::variables_map& vm)
{
    unsigned int seed = (unsigned int)std::time(nullptr);
    if (vm.count("seed"))
        seed = vm["seed"].as<unsigned int>();

    std::cout << "using seed: " << seed << std::endl;
    std::srand(seed);

    inplace_merge_test();
    inplace_merge_exception_test();
    inplace_merge_bad_alloc_test();

    std::cout << "Test Finish!" << std::endl;

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    // add command line option which controls the random number generator seed
    using namespace boost::program_options;
    options_description desc_commandline(
        "Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
        ("seed,s", value<unsigned int>(),
        "the random number generator seed to use for this run")
        ;

    // By default this test should run on all available cores
    std::vector<std::string> const cfg = {
        "hpx.os_threads=all"
    };

    // Initialize and run HPX
    HPX_TEST_EQ_MSG(hpx::init(desc_commandline, argc, argv, cfg), 0,
        "HPX main exited with non-zero status");

    return hpx::util::report_errors();
}
