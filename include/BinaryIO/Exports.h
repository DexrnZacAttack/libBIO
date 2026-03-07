//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#pragma once
#include "BinaryIO/Library.h"
#include "BinaryIO/Platform.h"

namespace bio {
#define BIO_GIT_LINK "https://codeberg.org/Dexrn/libBIO"

//why
#define BIO__STR(X) #X
#define BIO_STR(X) BIO__STR(X)

#ifndef BIO_CXX_STANDARD
#define BIO_CXX_STANDARD CPP_VERSION
#endif

#ifdef BIO_BIG_ENDIAN
#define BIO_BYTE_ORDER_NAME "Big"
#define BIO_BYTE_ORDER_SHORTNAME "be"
#else
#define BIO_BYTE_ORDER_NAME "Little"
#define BIO_BYTE_ORDER_SHORTNAME "le"
#endif

    constexpr const char *const LIBRARY_STRING = "libBIO v" BIO_VERSION " (" BIO_COMPILER_NAME " (C++" BIO_STR(BIO_CXX_STANDARD) ")" " / " BIO_BUILD_TYPE " | " BIO_PLATFORM_NAME " " BIO_PLATFORM_ARCH "-" BIO_BYTE_ORDER_SHORTNAME ") | " BIO_GIT_LINK;

    extern "C" {
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD int bio_get_platform_byte_order(void);
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD int bio_get_cpp_version(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_cpp_version_str(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_build_type(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_compiler_name(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform_byte_order_name(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform_arch(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_version(void); // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_library_string(void); // NOLINT
    }
} // namespace bio