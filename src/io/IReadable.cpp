//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/io/IReadable.h"

namespace bio::io {
    IReadable &IReadable::operator>>(uint8_t &b) {
        b = readByte();
        return *this;
    }
}
