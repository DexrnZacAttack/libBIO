//
// Created by DexrnZacAttack on 10/14/25 using zPc-i2.
//
#include "BinaryIO/Exports.h"

namespace bio {
    extern "C" {
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_cpp_version(void) { return BIO_CXX_STANDARD; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_build_type(void) { return BIO_BUILD_TYPE; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_compiler_name(void) { return BIO_COMPILER_NAME; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform_arch(void) { return BIO_PLATFORM_ARCH; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_platform(void) { return BIO_PLATFORM_NAME; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_version(void) { return BIO_VERSION; } // NOLINT
        TO_SECTION(".libbio.dexrn.me") BIO_API NO_DISCARD const char *bio_get_library_string(void) { return bio::LIBRARY_STRING; } // NOLINT
    }
}