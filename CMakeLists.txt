cmake_minimum_required(VERSION 3.31)
project(BIO VERSION 2.0.4)

set(VERSION_SUFFIX "") # used for non-stable versions, otherwise leave blank
set(CMAKE_CXX_STANDARD 17)

option(BIO_COMPILE_DOCS "Create documentation task" ON)

option(ENABLE_OPTIMIZATIONS "Enable compiler optimizations" ON)
if (ENABLE_OPTIMIZATIONS STREQUAL "ON")
    add_compile_options(
            "$<$<COMPILE_LANGUAGE:CXX>:-O3;-ffast-math;-march=native;-fpic;-ftree-vectorize>"
    )
endif ()
unset(ENABLE_OPTIMIZATIONS CACHE)

set(FILES
        include/BinaryIO/BinaryBuffer.h
        include/BinaryIO/Library.h
        include/BinaryIO/Exports.h
        src/BinaryBuffer.cpp
        src/Library.cpp
        include/BinaryIO/util/ByteOrder.h
        src/stream/BinaryInputStream.cpp
        include/BinaryIO/stream/BinaryInputStream.h
        include/BinaryIO/util/ISeekable.h
        include/BinaryIO/util/ByteOrderUtil.h
        include/BinaryIO/io/IReadable.h
        include/BinaryIO/io/IWritable.h
        src/util/string/StringConverter.cpp
        include/BinaryIO/util/string/StringConverter.h
        src/io/IReadable.cpp
        src/io/IWritable.cpp
        src/stream/BinaryOutputStream.cpp
        include/BinaryIO/stream/BinaryOutputStream.h
)

add_library(BIO-Static STATIC ${FILES})
add_library(BIO SHARED ${FILES})

set_target_properties(BIO-Static BIO PROPERTIES LINKER_LANGUAGE CXX) # CMake Error: CMake can not determine linker language for target: BinaryIO

target_include_directories(BIO-Static
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_include_directories(BIO
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_definitions(BIO-Static PRIVATE BIO_EXPORTS)
target_compile_definitions(BIO PRIVATE BIO_EXPORTS)

target_compile_definitions(BIO-Static PUBLIC
        BIO_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        BIO_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        BIO_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        BIO_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        BIO_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

target_compile_definitions(BIO PUBLIC
        BIO_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}"
        BIO_PLATFORM_NAME="${CMAKE_SYSTEM_NAME}"
        BIO_PLATFORM_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
        BIO_VERSION="${PROJECT_VERSION}${VERSION_SUFFIX}"
        BIO_RC_VERSION=${PROJECT_VERSION_MAJOR},${PROJECT_VERSION_MINOR},${PROJECT_VERSION_PATCH}
)

#set endianness define
if (CMAKE_CXX_BYTE_ORDER EQUAL BIG_ENDIAN)
    target_compile_definitions(BIO-Static PRIVATE IO_BIG_ENDIAN)
    target_compile_definitions(BIO PRIVATE IO_BIG_ENDIAN)
endif ()

if (BIO_COMPILE_DOCS)
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

        ADD_CUSTOM_TARGET(BIO-Docs
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                VERBATIM
        )
    ENDIF ()
endif ()