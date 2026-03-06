cmake_minimum_required(VERSION 3.31)
project(bio-cpp14-compile-test)

set(CMAKE_CXX_STANDARD 14)

set(TEST_FILES
        src/Tests.cpp
)

add_executable(bio-cpp14-compile-test ${TEST_FILES})

target_include_directories(bio-cpp14-compile-test
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(bio-cpp14-compile-test
        PRIVATE bio
)