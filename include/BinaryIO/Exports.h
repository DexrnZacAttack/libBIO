//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once
#include "BinaryIO/Library.h"
#include <algorithm>

namespace bio {
#define BIO_GIT_LINK "https://codeberg.org/Dexrn/libBIO"

    constexpr const char *const LIBRARY_STRING = "libBIO v" BIO_VERSION " (" BIO_COMPILER_NAME " (C++" BIO_CXX_STANDARD ")" " / " BIO_BUILD_TYPE " | " BIO_PLATFORM_NAME " " BIO_PLATFORM_ARCH ") | " BIO_GIT_LINK;

    extern "C" {
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_cpp_version(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_build_type(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_compiler_name(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform_arch(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_version(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_library_string(void); // NOLINT
    }
} // namespace bio