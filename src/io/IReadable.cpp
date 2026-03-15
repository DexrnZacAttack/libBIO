//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/io/interface/IReadable.h"

namespace bio {
    namespace io {
        namespace interface {
            uint32_t IReadable::readUint24() {
                return this->readUint24(util::ByteOrder::NATIVE);
            }

            int32_t IReadable::readInt24() {
                return this->readInt24(util::ByteOrder::NATIVE);
            }

            IReadable &IReadable::operator>>(uint8_t &b) {
                b = readByte();
                return *this;
            }
        }
    }
}
