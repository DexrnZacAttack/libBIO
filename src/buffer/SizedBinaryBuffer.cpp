//
// Created by DexrnZacAttack on 3/5/26 using zPc-i2.
//
#include "BinaryIO/buffer/SizedBinaryBuffer.h"

namespace bio::buffer {
    SizedBinaryBuffer::SizedBinaryBuffer(uint8_t *input, const size_t size) : BinaryBuffer(input), m_endPtr(input + size) {}

    SizedBinaryBuffer::SizedBinaryBuffer(const size_t size) : BinaryBuffer(size), m_endPtr(this->m_originPtr + size) {}

#if __cplusplus >= CPP20
    SizedBinaryBuffer::SizedBinaryBuffer(std::span<uint8_t> &input) : BinaryBuffer(input), m_endPtr(this->m_originPtr + input.size_bytes()) {}
#endif

    const uint8_t * SizedBinaryBuffer::ptrForOrigin(const util::Origin origin) const {
        switch (origin) {
        case util::EOrigin::END:
            return this->end();
        default:
            return BinaryBuffer::ptrForOrigin(origin);
        }
    }

    uint8_t * SizedBinaryBuffer::ptrForOrigin(const util::Origin origin) {
        switch (origin) {
        case util::EOrigin::END:
            return this->end();
        default:
            return BinaryBuffer::ptrForOrigin(origin);
        }
    }

    size_t SizedBinaryBuffer::size() const {
        return this->m_endPtr - this->m_originPtr;
    }

    uint8_t * SizedBinaryBuffer::end() {
        return this->m_endPtr;
    }

    const uint8_t * SizedBinaryBuffer::end() const {
        return this->m_endPtr;
    }

    bool SizedBinaryBuffer::eof() const {
        return this->m_positionPtr >= this->m_endPtr;
    }
}