//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "BinaryIO/Exports.h"

namespace bio {
    extern "C" {
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_build_type() { return BIO_BUILD_TYPE; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_compiler_name() { return BIO_COMPILER_NAME; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform_arch() { return BIO_PLATFORM_ARCH; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform() { return BIO_PLATFORM_NAME; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_version() { return BIO_VERSION; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_library_string() { return bio::LIBRARY_STRING; } // NOLINT
    }
}