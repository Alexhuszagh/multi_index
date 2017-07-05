#  :copyright: (c) 2017 Alex Huszagh.
#  :license: MIT, see licenses/mit.md for more details.

set(CMAKE_LEGACY_CYGWIN_WIN32 1)
cmake_minimum_required(VERSION 2.8)
project(multi_index CXX)
enable_testing()

# FLAGS
# -----

set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD TRUE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(UNIX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_definitions(-fPIC)
elseif(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd /O0 /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Ox /Zi /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} /MT /Zi /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /MT /Fd${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pdb")
endif()

# Need to manually set compiler flags for Travis CI & Appveyor
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

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
    test/test_mpl_ops.cpp
    test/test_observers.cpp
    test/test_projection.cpp
    test/test_range.cpp
    test/test_rearrange.cpp
    test/test_set_ops.cpp
    test/test_special_set_ops.cpp
    test/test_update.cpp
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
