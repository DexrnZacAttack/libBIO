cmake_minimum_required(VERSION 3.31)
project(bio VERSION 3.0.0)

set(VERSION_SUFFIX "") # used for non-stable versions, otherwise leave blank
include(CheckCXXCompilerFlag)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14) #default
endif()

if(CMAKE_CXX_STANDARD LESS 14)
    message(WARNING "C++14 or higher is required, libBIO may fail to build otherwise.")
endif()

option(ENABLE_OPTIMIZATIONS "Enable compiler optimizations" ON)
if (ENABLE_OPTIMIZATIONS STREQUAL "ON")
    add_compile_options(
            "$<$<COMPILE_LANGUAGE:CXX>:-O3;-ffast-math;-march=native;-fpic;-ftree-vectorize>"
    )
endif ()
unset(ENABLE_OPTIMIZATIONS CACHE)

set(FILES
        include/BinaryIO/buffer/BinaryBuffer.h
        include/BinaryIO/Library.h
        include/BinaryIO/Exports.h
        src/buffer/BinaryBuffer.cpp
        src/Library.cpp
        include/BinaryIO/util/ByteOrder.h
        src/stream/BinaryInputStream.cpp
        include/BinaryIO/stream/BinaryInputStream.h
        include/BinaryIO/io/ISeekable.h
        include/BinaryIO/util/ByteOrderUtil.h
        include/BinaryIO/io/IReadable.h
        include/BinaryIO/io/IWritable.h
        src/util/string/StringConverter.cpp
        include/BinaryIO/util/string/StringConverter.h
        src/io/IReadable.cpp
        src/io/IWritable.cpp
        src/stream/BinaryOutputStream.cpp
        include/BinaryIO/stream/BinaryOutputStream.h
        include/BinaryIO/buffer/BinaryBuffer.tpp
        include/BinaryIO/Platform.h
        include/BinaryIO/io/IBuffer.h
        include/BinaryIO/buffer/SizedBinaryBuffer.h
        src/buffer/SizedBinaryBuffer.cpp
        include/BinaryIO/stream/BinaryInputStream.tpp
        include/BinaryIO/stream/BinaryOutputStream.tpp
        include/BinaryIO/io/ISimplePeekable.h
)

add_library(bio-static STATIC ${FILES})

option(ENABLE_SHARED_BUILD "Enable shared library building" ON)
if (ENABLE_SHARED_BUILD STREQUAL "ON")
    add_library(bio SHARED ${FILES})
else()
    add_library(bio STATIC ${FILES})
endif()
unset(ENABLE_SHARED_BUILD CACHE)

set_target_properties(bio-static bio PROPERTIES LINKER_LANGUAGE CXX) # CMake Error: CMake can not determine linker language for target: BinaryIO

target_include_directories(bio-static
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_include_directories(bio
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_definitions(bio-static PRIVATE BIO_EXPORTS)
target_compile_definitions(bio PRIVATE BIO_EXPORTS)

target_compile_definitions(bio-static PUBLIC
        BIO_CXX_STANDARD="${CMAKE_CXX_STANDARD}"
        BIO_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
        BIO_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        BIO_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        BIO_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        BIO_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        BIO_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

target_compile_definitions(bio PUBLIC
        BIO_CXX_STANDARD="${CMAKE_CXX_STANDARD}"
        BIO_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
        BIO_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        BIO_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        BIO_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        BIO_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        BIO_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

#set endianness define
if (CMAKE_CXX_BYTE_ORDER EQUAL BIG_ENDIAN)
    target_compile_definitions(bio-static PRIVATE IO_BIG_ENDIAN)
    target_compile_definitions(bio PRIVATE IO_BIG_ENDIAN)
endif ()

set(ALLOW_CPP17_EXTENSIONS_DEFAULT OFF)
if (NOT CXX_EXTENSIONS STREQUAL OFF)
    set(ALLOW_CPP17_EXTENSIONS_DEFAULT ON)
endif()

option(ALLOW_CPP17_EXTENSIONS "Allow C++17 extensions in C++14" ${ALLOW_CPP17_EXTENSIONS_DEFAULT})
if (ALLOW_CPP17_EXTENSIONS STREQUAL ON)
    target_compile_definitions(bio-static PUBLIC BIO_ALLOW_CPP17_EXTENSIONS)
    target_compile_definitions(bio PUBLIC BIO_ALLOW_CPP17_EXTENSIONS)
endif ()
unset(ALLOW_CPP17_EXTENSIONS CACHE)

option(BIO_COMPILE_DOCS "Create documentation task" ON)
if (BIO_COMPILE_DOCS STREQUAL "ON")
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

        ADD_CUSTOM_TARGET(bio-docs
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                VERBATIM
        )
    ENDIF ()
endif ()
unset(BIO_COMPILE_DOCS CACHE)

option(BIO_TESTS "Build libBIO tests" OFF)
    add_subdirectory("tests")
unset(BIO_TESTS CACHE)