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
    constexpr const char *const LIBRARY_STRING = "libBIO v" BIO_VERSION " (" BIO_COMPILER_NAME " / " BIO_BUILD_TYPE " | " BIO_PLATFORM_NAME " " BIO_PLATFORM_ARCH ") | https://github.com/DexrnZacAttack/libBIO";

    extern "C" {
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_build_type(); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_compiler_name(); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform_arch(); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform(); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_version(); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_library_string(); // NOLINT
    }
} // namespace bio