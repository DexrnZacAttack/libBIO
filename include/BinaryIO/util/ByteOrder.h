//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_BYTEORDER_H
#define BIO_BYTEORDER_H

#include "BinaryIO/Library.h"

namespace bio::util {
    /** Byte Order/Endian dictates which way bytes are written */
    enum class BIO_API ByteOrder {
        BIG,   /**< Big Endian | Writes 0xA1B2C3D4 */
        LITTLE /**< Little Endian | Writes 0xD4C3B2A1 */
    };
}

#endif //BIO_BYTEORDER_H