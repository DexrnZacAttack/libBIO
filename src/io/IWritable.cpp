//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/io/IWritable.h"

namespace bio::io {
    void IWritable::writeUint24(const uint32_t v) {
        this->writeUint24(v, util::ByteOrder::PLATFORM);
    }

    void IWritable::writeInt24(const int32_t v) {
        this->writeInt24(v, util::ByteOrder::PLATFORM);
    }

    IWritable &IWritable::operator<<(const uint8_t b) {
        writeByte(b);
        return *this;
    }
}
