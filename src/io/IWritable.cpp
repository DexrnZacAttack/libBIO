//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/io/IWritable.h"

namespace bio::io {
    IWritable &IWritable::operator<<(const uint8_t b) {
        writeByte(b);
        return *this;
    }
}
