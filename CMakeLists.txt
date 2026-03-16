cmake_minimum_required(VERSION 3.31)
project(bio VERSION 4.0.0)

set(VERSION_SUFFIX "-dev.3") # used for non-stable versions, otherwise leave blank
include(CheckCXXCompilerFlag)

if(CMAKE_CXX_STANDARD LESS 14)
    message(FATAL_ERROR "libBIO requires C++14 or higher.")
endif()

set(FILES
        include/BinaryIO/buffer/BinaryBuffer.h
        include/BinaryIO/Library.h
        include/BinaryIO/Exports.h
        src/buffer/BinaryBuffer.cpp
        src/Library.cpp
        include/BinaryIO/util/ByteOrder.h
        src/stream/BinaryInputStream.cpp
        include/BinaryIO/stream/BinaryInputStream.h
        include/BinaryIO/io/interface/ISeekable.h
        include/BinaryIO/util/ByteOrderUtil.h
        include/BinaryIO/io/interface/IReadable.h
        include/BinaryIO/io/interface/IWritable.h
        src/util/string/StringConverter.cpp
        include/BinaryIO/util/string/StringConverter.h
        src/io/IReadable.cpp
        src/io/IWritable.cpp
        src/stream/BinaryOutputStream.cpp
        include/BinaryIO/stream/BinaryOutputStream.h
        include/BinaryIO/buffer/BinaryBuffer.tpp
        include/BinaryIO/Platform.h
        include/BinaryIO/io/interface/IBuffer.h
        include/BinaryIO/buffer/SizedBinaryBuffer.h
        src/buffer/SizedBinaryBuffer.cpp
        include/BinaryIO/stream/BinaryInputStream.tpp
        include/BinaryIO/stream/BinaryOutputStream.tpp
        include/BinaryIO/io/interface/ISimplePeekable.h
        include/BinaryIO/io/interface/IPeekable.h
        include/BinaryIO/util/Origin.h
        include/BinaryIO/buffer/SizedBinaryBuffer.tpp
        include/BinaryIO/io/Serializable.h
        include/BinaryIO/container/FixedArray.h
        include/BinaryIO/io/interface/IAccessible.h
        include/BinaryIO/io/iter/Iterator.h
        include/BinaryIO/io/interface/ICanDeserialize.h
        include/BinaryIO/io/interface/ICanSerialize.h
        include/BinaryIO/util/string/StringLengthEncoding.h
)

set(BIO_TARGETS bio bio-static)
set(BIO_TARGET_TYPES SHARED STATIC)
set(BIO_CPP_VERSIONS
        14
        17
        20
        23
        ""
)

list(LENGTH BIO_TARGETS tc)
math(EXPR lastTarget "${tc} - 1")

foreach(version IN LISTS BIO_CPP_VERSIONS)
    foreach(i RANGE ${lastTarget})
        list(GET BIO_TARGETS ${i} target)
        list(GET BIO_TARGET_TYPES ${i} targetType)

        if (NOT ${version} STREQUAL "")
            set(targetName ${target}-cpp${version})
        else ()
            set(targetName ${target})
        endif()

        add_library(${targetName} ${targetType} ${FILES})
        set_target_properties(${targetName} PROPERTIES
                LINKER_LANGUAGE CXX)

        if (NOT ${version} STREQUAL "")
            set_target_properties(${targetName} PROPERTIES
                    CXX_STANDARD ${version}
                    CXX_STANDARD_REQUIRED ON
                    CXX_EXTENSIONS OFF
            )
        endif()

        message(STATUS "Created ${targetName}")

        target_include_directories(${targetName}
                PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )

        target_compile_definitions(${targetName} PRIVATE BIO_EXPORTS)

        target_compile_definitions(${targetName} PUBLIC
                BIO_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
                BIO_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
                BIO_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
                BIO_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
                BIO_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
                BIO_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
        )

        option(BIO_ENABLE_OPTIMIZATIONS "Enable compiler optimizations" ON)
        if (BIO_ENABLE_OPTIMIZATIONS STREQUAL "ON")
            if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
                target_compile_options(${targetName} PRIVATE -O3 -ffast-math -march=native -fpic -ftree-vectorize)
            endif()
        endif ()
        unset(BIO_ENABLE_OPTIMIZATIONS CACHE)

        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            target_compile_options(${targetName} PRIVATE -fno-inline-functions -g3 -gdwarf-5 -fno-eliminate-unused-debug-types)
            if (CMAKE_CXX_COMPILER_ID STREQUAL "GCC")
                target_compile_options(${targetName} PRIVATE -fvar-tracking -fvar-tracking-assignments)
            endif()
            if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
                target_compile_options(${targetName} PRIVATE -fstandalone-debug)
            endif()
        endif()

        #set endianness define
        if (CMAKE_CXX_BYTE_ORDER STREQUAL BIG_ENDIAN)
            target_compile_definitions(${targetName} PUBLIC BIO_BIG_ENDIAN)
        endif ()

        set(ALLOW_CPP17_EXTENSIONS_DEFAULT OFF)
        if (NOT CXX_EXTENSIONS STREQUAL OFF)
            set(ALLOW_CPP17_EXTENSIONS_DEFAULT ON)
        endif()

        option(ALLOW_CPP17_EXTENSIONS "Allow C++17 extensions in C++14" ${ALLOW_CPP17_EXTENSIONS_DEFAULT})
        if (ALLOW_CPP17_EXTENSIONS STREQUAL ON)
            target_compile_definitions(${targetName} PUBLIC BIO_ALLOW_CPP17_EXTENSIONS)
        endif ()
        unset(ALLOW_CPP17_EXTENSIONS CACHE)

    endforeach()
endforeach()

option(BIO_DOCS_TARGET "Create documentation target" ON)
if (BIO_DOCS_TARGET STREQUAL "ON")
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
        set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in")
        set(DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")

        CONFIGURE_FILE(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

        ADD_CUSTOM_TARGET(bio-docs
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                VERBATIM
        )
    ENDIF ()
endif ()
unset(BIO_DOCS_TARGET CACHE)

option(BIO_TESTS "Build libBIO tests" ON)
if (BIO_TESTS STREQUAL "ON")
    add_subdirectory("tests")
endif()

unset(BIO_TESTS CACHE)