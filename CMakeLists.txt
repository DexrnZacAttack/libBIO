cmake_minimum_required(VERSION 4.0)
project(BIO VERSION 1.0.0)

set(VERSION_SUFFIX "") # used for non-stable versions, otherwise leave blank
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DCOMPILER_NAME="${CMAKE_CXX_COMPILER_ID}")
add_definitions(-DPLATFORM_NAME="${CMAKE_SYSTEM_NAME}")
add_definitions(-DPLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}")

option(ENABLE_OPTIMIZATIONS "Enable compiler optimizations" ON)
if (ENABLE_OPTIMIZATIONS STREQUAL "ON")
    add_compile_options(
            "$<$<COMPILE_LANGUAGE:CXX>:-O3;-ffast-math;-march=native;-fpic;-ftree-vectorize>"
    )
endif ()
unset(ENABLE_OPTIMIZATIONS CACHE)

set(HEADERS
        include/BinaryIO.h
        include/Library.h
        include/Exports.h)

set(SOURCES
        src/BinaryIO.cpp
        src/BinaryString.cpp
        src/Library.cpp)

add_library(BIO STATIC ${HEADERS} ${SOURCES})
set_target_properties(BIO PROPERTIES LINKER_LANGUAGE CXX) # CMake Error: CMake can not determine linker language for target: BinaryIO

target_include_directories(BIO PUBLIC "include" "src")
target_compile_definitions(BIO PRIVATE BIO_EXPORTS)

target_compile_definitions(BIO PRIVATE
        BIO_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        BIO_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

#set endianness define
if (CMAKE_CXX_BYTE_ORDER EQUAL BIG_ENDIAN)
    target_compile_definitions(BIO PRIVATE IO_BIG_ENDIAN)
endif ()