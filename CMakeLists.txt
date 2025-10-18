cmake_minimum_required(VERSION 3.31)
project(BIO VERSION 1.0.1)

set(VERSION_SUFFIX "") # used for non-stable versions, otherwise leave blank
set(CMAKE_CXX_STANDARD 17)

option(COMPILE_DOCS "Create documentation task" ON)

option(ENABLE_OPTIMIZATIONS "Enable compiler optimizations" ON)
if (ENABLE_OPTIMIZATIONS STREQUAL "ON")
    add_compile_options(
            "$<$<COMPILE_LANGUAGE:CXX>:-O3;-ffast-math;-march=native;-fpic;-ftree-vectorize>"
    )
endif ()
unset(ENABLE_OPTIMIZATIONS CACHE)

set(HEADERS
        include/BinaryIO/BinaryIO.h
        include/BinaryIO/Library.h
        include/BinaryIO/Exports.h)

set(SOURCES
        src/BinaryIO.cpp
        src/BinaryString.cpp
        src/Library.cpp)

add_library(BIO STATIC ${HEADERS} ${SOURCES})
set_target_properties(BIO PROPERTIES LINKER_LANGUAGE CXX) # CMake Error: CMake can not determine linker language for target: BinaryIO

target_include_directories(BIO
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/BinaryIO
)
target_compile_definitions(BIO PRIVATE BIO_EXPORTS)

target_compile_definitions(BIO PRIVATE
        BIO_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        BIO_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        BIO_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        BIO_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        BIO_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

#set endianness define
if (CMAKE_CXX_BYTE_ORDER EQUAL BIG_ENDIAN)
    target_compile_definitions(BIO PRIVATE IO_BIG_ENDIAN)
endif ()

if (COMPILE_DOCS)
    include(FetchContent)
    # https://github.com/jothepro/doxygen-awesome-css?tab=readme-ov-file#cmake-with-fetchcontent
    FetchContent_Declare(
            doxygen-awesome-css
            URL https://github.com/jothepro/doxygen-awesome-css/archive/refs/heads/main.zip
    )
    FetchContent_MakeAvailable(doxygen-awesome-css)

    FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

    FIND_PACKAGE(Doxygen)
    IF (DOXYGEN_FOUND)
        set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        CONFIGURE_FILE(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

        ADD_CUSTOM_TARGET(bio_docs
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                VERBATIM
        )
    ENDIF ()
endif()