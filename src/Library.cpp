//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "Exports.h"

namespace bio {
    extern "C" {
        constexpr const char *bio_get_build_type() { return BIO_BUILD_TYPE; } // NOLINT
        constexpr const char *bio_get_compiler_name() { return BIO_COMPILER_NAME; } // NOLINT
        constexpr const char *bio_get_platform_arch() { return BIO_PLATFORM_ARCH; } // NOLINT
        constexpr const char *bio_get_platform() { return BIO_PLATFORM_NAME; } // NOLINT
        constexpr const char *bio_get_version() { return BIO_VERSION; } // NOLINT
        constexpr const char *bio_get_library_string() { return bio::LIBRARY_STRING; } // NOLINT
    }
}