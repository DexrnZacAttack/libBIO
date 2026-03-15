//
// Created by (Person who prefers not to be named) and DexrnZacAttack on
// 20/12/2024.
//

#include <cstring>
#include <vector>

#include "BinaryIO/buffer/BinaryBuffer.h"

namespace bio {
    namespace buffer {
        BinaryBuffer::BinaryBuffer(
            container::FixedArray<uint8_t> &input) : m_originPtr(
            input.startPtr()) {
        }

#if __cplusplus >= CPP20
        BinaryBuffer::BinaryBuffer(std::span<uint8_t> &input) : BinaryBuffer(
            input.data()) {
        }
#endif

        BinaryBuffer::~BinaryBuffer() {
            if (this->m_owned) //if we own the ptr, we need to destroy it
                delete[] this->m_originPtr;
        }

        BinaryBuffer::BinaryBuffer(std::vector<uint8_t> &input) : BinaryBuffer(
            input.data()) {
        }

        BinaryBuffer::BinaryBuffer(uint8_t *input) : m_originPtr(input) {
        }

        BinaryBuffer::BinaryBuffer(const size_t size) : m_originPtr(
            new uint8_t[size]{}), m_owned(true) {
        }

        void BinaryBuffer::seek(const size_t offset) {
            this->m_positionPtr = this->m_originPtr + offset;
        }

        void BinaryBuffer::seekRelative(const size_t offset) {
            this->m_positionPtr += offset;
        }

        bool BinaryBuffer::canSeek() const {
            return true;
        }

        size_t BinaryBuffer::getOffset() const {
            return this->m_positionPtr - this->m_originPtr;
        }

        uint8_t BinaryBuffer::readByte() { return *this->m_positionPtr++; }

        uint8_t BinaryBuffer::peekByte(const util::Origin origin,
                                       const size_t offset) const {
            return *(this->ptrForOrigin(origin) + offset);
        }

        int8_t BinaryBuffer::readSignedByte() {
            return static_cast<int8_t>(*this->m_positionPtr++);
        }

        int8_t BinaryBuffer::peekSignedByte(const util::Origin origin,
                                            const size_t offset) const {
            return static_cast<int8_t>(*(this->ptrForOrigin(origin) + offset));
        }

        uint32_t BinaryBuffer::readUint24(const bio::util::ByteOrder endian) {
            const uint8_t b0 = readByte();
            const uint8_t b1 = readByte();
            const uint8_t b2 = readByte();

            if (endian == bio::util::ByteOrder::LITTLE)
                return static_cast<uint32_t>(b0)
                       | (static_cast<uint32_t>(b1) << 8)
                       | (static_cast<uint32_t>(b2) << 16);

            return (static_cast<uint32_t>(b0) << 16)
                   | (static_cast<uint32_t>(b1) << 8)
                   | static_cast<uint32_t>(b2);
        }

        uint32_t BinaryBuffer::peekUint24(const bio::util::ByteOrder endian,
                                          const util::Origin origin,
                                          const size_t offset) const {
            const uint8_t b0 = this->peekByte(origin, offset);
            const uint8_t b1 = this->peekByte(origin, offset + 1);
            const uint8_t b2 = this->peekByte(origin, offset + 2);

            if (endian == bio::util::ByteOrder::LITTLE)
                return static_cast<uint32_t>(b0)
                       | (static_cast<uint32_t>(b1) << 8)
                       | (static_cast<uint32_t>(b2) << 16);

            return (static_cast<uint32_t>(b0) << 16)
                   | (static_cast<uint32_t>(b1) << 8)
                   | static_cast<uint32_t>(b2);
        }

        int32_t BinaryBuffer::readInt24(const bio::util::ByteOrder endian) {
            uint32_t res = readUint24(endian);

            if (res & (1 << 23)) {
                res |= 0xFF000000;
            }

            return static_cast<int32_t>(res);
        }

        int32_t BinaryBuffer::peekInt24(const bio::util::ByteOrder endian,
                                        const util::Origin origin,
                                        const size_t offset) const {
            uint32_t res = this->peekUint24(endian, origin, offset);

            if (res & (1 << 23)) {
                res |= 0xFF000000;
            }

            return static_cast<int32_t>(res);
        }

        void BinaryBuffer::writeByte(const uint8_t v) {
            *this->m_positionPtr++ = v;
        }

        void BinaryBuffer::writeBytes(const uint8_t *v, const size_t size) {
            std::memcpy(this->m_positionPtr, v, size);
            this->m_positionPtr += size;
        }

        void BinaryBuffer::writeSignedByte(const int8_t v) {
            *this->m_positionPtr++ = static_cast<uint8_t>(v);
        }

        uint8_t *BinaryBuffer::ptrForOrigin(const util::Origin origin) {
            switch (origin) {
            case util::EOrigin::START:
                return this->begin();
            case util::EOrigin::CURRENT_POSITION:
                return this->position();
            default:
                return nullptr;
            }
        }

        const uint8_t *BinaryBuffer::ptrForOrigin(
            const util::Origin origin) const {
            switch (origin) {
            case util::EOrigin::START:
                return this->begin();
            case util::EOrigin::CURRENT_POSITION:
                return this->position();
            default:
                return nullptr;
            }
        }

        uint8_t *BinaryBuffer::begin() { return this->m_originPtr; }

        uint8_t *BinaryBuffer::position() { return this->m_positionPtr; }

        const uint8_t *BinaryBuffer::begin() const { return this->m_originPtr; }

        const uint8_t *BinaryBuffer::position() const {
            return this->m_positionPtr;
        }

        uint8_t *BinaryBuffer::readOfSize(const size_t sz) {
            uint8_t *result = new uint8_t[sz];
            std::memcpy(result, this->m_positionPtr, sz);
            this->m_positionPtr += sz;
            return result;
        }

        uint8_t *BinaryBuffer::peekOfSize(const size_t sz,
                                          const util::Origin origin,
                                          const size_t offset) const {
            uint8_t *result = new uint8_t[sz];
            std::memcpy(result, this->ptrForOrigin(origin) + offset, sz);
            return result;
        }

        std::vector<uint8_t> BinaryBuffer::readOfSizeVec(const size_t sz) {
            std::vector<uint8_t> result(this->m_positionPtr,
                                        this->m_positionPtr + sz);
            this->m_positionPtr += sz;
            return result;
        }

        std::vector<uint8_t> BinaryBuffer::peekOfSizeVec(
            const size_t sz, const util::Origin origin,
            const size_t offset) const {
            const uint8_t *p = this->ptrForOrigin(origin) + offset;
            return std::vector<uint8_t>(p, p + sz);
        }

        void BinaryBuffer::readInto(uint8_t *into, const size_t sz) {
            std::memcpy(into, this->m_positionPtr, sz);
            this->m_positionPtr += sz;
        }

        void BinaryBuffer::peekInto(uint8_t *into, const size_t sz,
                                    const util::Origin origin,
                                    const size_t offset) const {
            std::memcpy(into, this->ptrForOrigin(origin) + offset, sz);
        }

#if __cplusplus >= CPP20
        std::span<uint8_t> BinaryBuffer::getView(const size_t sz) {
            return std::span(this->position(), this->position() + sz);
        }

        std::span<const uint8_t> BinaryBuffer::getView(const size_t sz) const {
            return std::span(this->position(), this->position() + sz);
        }
#endif

        uint8_t &BinaryBuffer::operator[](const size_t i) {
            return m_originPtr[i];
        }

        const uint8_t &BinaryBuffer::operator[](const size_t i) const {
            return m_originPtr[i];
        }

        io::interface::ISeekable &BinaryBuffer::operator+=(const size_t amount) {
            this->m_positionPtr += amount;
            return *this;
        }

        io::interface::ISeekable &BinaryBuffer::operator-=(const size_t amount) {
            this->m_positionPtr -= amount;
            return *this;
        }

        void BinaryBuffer::writeUint24(const uint32_t v,
                                       const bio::util::ByteOrder endian) {
            const uint8_t b0 = static_cast<uint8_t>(v & 0xFF);
            const uint8_t b1 = static_cast<uint8_t>((v >> 8) & 0xFF);
            const uint8_t b2 = static_cast<uint8_t>((v >> 16) & 0xFF);

            if (endian == bio::util::ByteOrder::LITTLE) {
                writeByte(b0);
                writeByte(b1);
                writeByte(b2);
            } else {
                writeByte(b2);
                writeByte(b1);
                writeByte(b0);
            }
        }

        void BinaryBuffer::writeInt24(const int32_t v,
                                      const bio::util::ByteOrder endian) {
            writeUint24(static_cast<uint32_t>(v), endian);
        }
    }
} // namespace lce::io
