cmake_minimum_required(VERSION 3.31)
project(bio VERSION 3.1.0)

set(VERSION_SUFFIX "") # used for non-stable versions, otherwise leave blank
include(CheckCXXCompilerFlag)

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
        include/BinaryIO/io/IPeekable.h
        include/BinaryIO/util/Origin.h
        include/BinaryIO/buffer/SizedBinaryBuffer.tpp
)

add_library(bio-static STATIC ${FILES})
add_library(bio SHARED ${FILES})

set(BIO_TARGETS bio bio-static)

set_target_properties(bio-static bio PROPERTIES LINKER_LANGUAGE CXX) # CMake Error: CMake can not determine linker language for target: BinaryIO

foreach(target IN LISTS BIO_TARGETS)

    target_include_directories(${target}
            PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

    target_compile_definitions(${target} PRIVATE BIO_EXPORTS)

    target_compile_definitions(${target} PUBLIC
            BIO_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
            BIO_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
            BIO_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
            BIO_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
            BIO_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
            BIO_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
    )

    if (CMAKE_CXX_STANDARD)
        target_compile_definitions(${target} PUBLIC
                BIO_CXX_STANDARD=${CMAKE_CXX_STANDARD}
        )
    endif()

    #set endianness define
    if (CMAKE_CXX_BYTE_ORDER STREQUAL BIG_ENDIAN)
        target_compile_definitions(${target} PUBLIC BIO_BIG_ENDIAN)
    endif ()

    set(ALLOW_CPP17_EXTENSIONS_DEFAULT OFF)
    if (NOT CXX_EXTENSIONS STREQUAL OFF)
        set(ALLOW_CPP17_EXTENSIONS_DEFAULT ON)
    endif()

    option(ALLOW_CPP17_EXTENSIONS "Allow C++17 extensions in C++14" ${ALLOW_CPP17_EXTENSIONS_DEFAULT})
    if (ALLOW_CPP17_EXTENSIONS STREQUAL ON)
        target_compile_definitions(${target} PUBLIC BIO_ALLOW_CPP17_EXTENSIONS)
    endif ()
    unset(ALLOW_CPP17_EXTENSIONS CACHE)

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
unset(BIO_DOCS_TARGET CACHE)

option(BIO_TESTS "Build libBIO tests" ON)
if (BIO_TESTS STREQUAL "ON")
    add_subdirectory("tests")
endif()

unset(BIO_TESTS CACHE)