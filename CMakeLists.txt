#  :copyright: (c) 2017 Alex Huszagh.
#  :license: MIT, see licenses/mit.md for more details.

set(CMAKE_LEGACY_CYGWIN_WIN32 1)
cmake_minimum_required(VERSION 2.8)
project(multi_index CXX)
enable_testing()

# FLAGS
# -----

set(CMAKE_CXX_STANDARD 11)
set(CXX_STANDARD TRUE)

# OPTIONS
#option(BUILD_TESTS "Build pycpp library tests" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# TESTS
# -----

set(TEST_FILES
    test/test_all_main.cpp
    test/test_basic.cpp
    test/test_capacity.cpp
    test/test_comparison.cpp
    test/test_composite_key.cpp
    test/test_conv_iterators.cpp
    test/test_copy_assignment.cpp
    test/test_hash_ops.cpp
    test/test_iterators.cpp
    test/test_key_extractors.cpp
    test/test_list_ops.cpp
    test/test_modifiers.cpp
)

add_executable(multi_index_tests ${TEST_FILES})

if(MSVC)
    set_target_properties(multi_index_tests PROPERTIES
        COMPILE_OPTIONS "/EHsc"
    )
endif()

add_test(NAME multi_index_tests
    COMMAND multi_index_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
