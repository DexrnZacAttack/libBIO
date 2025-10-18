//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once
#include "BinaryIO/Library.h"

#if CMAKE_BUILD_DEBUG
#define BIO_BUILD_TYPE "Debug"
#else
#define BIO_BUILD_TYPE "Release"
#endif

namespace bio {
    // was gonna use me.dexrn but afaik section naming usually starts with a dot
    TO_SECTION(".dexrn.me") // constant exec segment to see library string
    constexpr const char *const LIBRARY_STRING = "libBIO v" BIO_VERSION " (" BIO_COMPILER_NAME " / " BIO_BUILD_TYPE " | " BIO_PLATFORM_NAME " " BIO_PLATFORM_ARCH ") | https://github.com/DexrnZacAttack/libBIO";

    extern "C" {
        BIO_API NO_DISCARD constexpr const char *bio_get_build_type(); // NOLINT
        BIO_API NO_DISCARD constexpr const char *bio_get_compiler_name(); // NOLINT
        BIO_API NO_DISCARD constexpr const char *bio_get_platform_arch(); // NOLINT
        BIO_API NO_DISCARD constexpr const char *bio_get_platform(); // NOLINT
        BIO_API NO_DISCARD constexpr const char *bio_get_version(); // NOLINT
        BIO_API NO_DISCARD constexpr const char *bio_get_library_string(); // NOLINT
    }
} // namespace bio