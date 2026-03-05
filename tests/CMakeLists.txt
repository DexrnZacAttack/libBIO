cmake_minimum_required(VERSION 3.31)
project(BIO-TESTS)

set(CMAKE_CXX_STANDARD 23)

set(TEST_FILES
        include/BinaryIO/Tests/Tests.h
        src/Tests.cpp
        include/BinaryIO/Tests/util/Random.h
        include/BinaryIO/Tests/util/Output.h
)

include(FetchContent)
FetchContent_Declare(tfw
        GIT_REPOSITORY https://codeberg.org/Dexrn/TFW
        GIT_TAG        main
        GIT_PROGRESS   TRUE
        GIT_SHALLOW    TRUE
        EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(tfw)

add_executable(BIO-Tests ${TEST_FILES})

target_include_directories(BIO-Tests
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(BIO-Tests
        PRIVATE BIO
        PRIVATE tfw
)