//
// Created by (Person who prefers not to be named) and DexrnZacAttack on
// 20/12/2024.
//

#include <cstring>
#include <vector>

#include "../../include/BinaryIO/buffer/BinaryBuffer.h"

namespace bio::buffer {
#if __cplusplus >= CPP20
    BinaryBuffer::BinaryBuffer(std::span<uint8_t> &input) : BinaryBuffer(input.data()) {}
#endif

    BinaryBuffer::~BinaryBuffer() {
        if (this->m_owned) //if we own the ptr, we need to destroy it
            delete[] this->m_originPtr;
    }

    BinaryBuffer::BinaryBuffer(std::vector<uint8_t> &input) : BinaryBuffer(input.data()) {
    }

    BinaryBuffer::BinaryBuffer(uint8_t *input) : m_originPtr(input) {
    }

    BinaryBuffer::BinaryBuffer(const size_t size) : m_originPtr(new uint8_t[size]{}), m_owned(true) {
    }

    void BinaryBuffer::seek(const size_t offset) {
        this->m_positionPtr = this->m_originPtr + offset;
    }

    void BinaryBuffer::seekRelative(const size_t offset) { this->m_positionPtr += offset; }

    bool BinaryBuffer::canSeek() const {
        return true;
    }

    size_t BinaryBuffer::getOffset() const { return this->m_positionPtr - this->m_originPtr; }

    uint8_t BinaryBuffer::readByte() { return *this->m_positionPtr++; }

    uint8_t BinaryBuffer::peekByte(const util::Origin origin, const size_t offset) const {
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
             |  static_cast<uint32_t>(b2);
    }

    uint32_t BinaryBuffer::peekUint24(const bio::util::ByteOrder endian, const util::Origin origin, const size_t offset) const {
        const uint8_t b0 = this->peekByte(origin, offset);
        const uint8_t b1 = this->peekByte(origin, offset + 1);
        const uint8_t b2 = this->peekByte(origin, offset + 2);

        if (endian == bio::util::ByteOrder::LITTLE)
            return static_cast<uint32_t>(b0)
                | (static_cast<uint32_t>(b1) << 8)
                | (static_cast<uint32_t>(b2) << 16);

        return (static_cast<uint32_t>(b0) << 16)
             | (static_cast<uint32_t>(b1) << 8)
             |  static_cast<uint32_t>(b2);
    }

    int32_t BinaryBuffer::readInt24(const bio::util::ByteOrder endian) {
        uint32_t res = readUint24(endian);

        if (res & (1 << 23)) {
            res |= 0xFF000000;
        }

        return static_cast<int32_t>(res);
    }

    int32_t BinaryBuffer::peekInt24(const bio::util::ByteOrder endian, const util::Origin origin, const size_t offset) const {
        uint32_t res = this->peekUint24(endian, origin, offset);

        if (res & (1 << 23)) {
            res |= 0xFF000000;
        }

        return static_cast<int32_t>(res);
    }

    void BinaryBuffer::writeByte(const uint8_t v) { *this->m_positionPtr++ = v; }

    void BinaryBuffer::writeBytes(const uint8_t *v, const size_t size) {
        std::memcpy(this->m_positionPtr, v, size);
        this->m_positionPtr += size;
    }

    void BinaryBuffer::writeSignedByte(const int8_t v) {
        *this->m_positionPtr++ = static_cast<uint8_t>(v);
    }

    uint8_t * BinaryBuffer::ptrForOrigin(const util::Origin origin) {
        switch (origin) {
        case util::EOrigin::START:
            return this->begin();
        case util::EOrigin::CURRENT_POSITION:
            return this->position();
        default:
            return nullptr;
        }
    }

    const uint8_t * BinaryBuffer::ptrForOrigin(const util::Origin origin) const {
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

    const uint8_t *BinaryBuffer::position() const { return this->m_positionPtr; }

    uint8_t *BinaryBuffer::readOfSize(const size_t sz) {
        uint8_t *result = new uint8_t[sz];
        std::memcpy(result, this->m_positionPtr, sz);
        this->m_positionPtr += sz;
        return result;
    }

    uint8_t * BinaryBuffer::peekOfSize(const size_t sz, const util::Origin origin, const size_t offset) const {
        uint8_t *result = new uint8_t[sz];
        std::memcpy(result, this->ptrForOrigin(origin) + offset, sz);
        return result;
    }

    std::vector<uint8_t> BinaryBuffer::readOfSizeVec(const size_t sz) {
        std::vector<uint8_t> result(this->m_positionPtr, this->m_positionPtr + sz);
        this->m_positionPtr += sz;
        return result;
    }

    std::vector<uint8_t> BinaryBuffer::peekOfSizeVec(const size_t sz, const util::Origin origin, const size_t offset) const {
        const uint8_t *p = this->ptrForOrigin(origin) + offset;
        return std::vector<uint8_t>(p, p + sz);
    }

    void BinaryBuffer::readInto(uint8_t *into, const size_t sz) {
        std::memcpy(into, this->m_positionPtr, sz);
        this->m_positionPtr += sz;
    }

    void BinaryBuffer::peekInto(uint8_t *into, const size_t sz, const util::Origin origin, const size_t offset) const {
        std::memcpy(into, this->ptrForOrigin(origin) + offset, sz);
    }

    std::string BinaryBuffer::readString(const size_t size) {
        std::string result(size, '\0');
        readInto(reinterpret_cast<uint8_t *>(&result[0]), size);

        return result;
    }

    std::string BinaryBuffer::readStringNT() {
        // I believe this should find the next null byte, which can replace most of this method's bulk
        const size_t len = std::strlen(reinterpret_cast<const char *>(this->m_positionPtr));
        std::string r(reinterpret_cast<const char *>(this->m_positionPtr), len);

        this->m_positionPtr += len + 1;

        return r;
    }

    std::u16string BinaryBuffer::readU16String(const size_t size,
                                               const util::ByteOrder endian) {
        std::u16string res(size, u'\0');
        readInto(reinterpret_cast<uint8_t *>(&res[0]), size * sizeof(char16_t));

        // this converts endianness to system native
        // otherwise string would be garbled unicode slop
#if defined(BR_BIG_ENDIAN)
        if (endian == util::ByteOrder::LITTLE) {
#else
        if (endian == util::ByteOrder::BIG) {
#endif
            for (char16_t &c: res) {
                c = util::ByteOrderUtil::swapOrder(c);
            }
        }

        return res;
    }

    std::u16string BinaryBuffer::readU16StringNT(const util::ByteOrder endian) {
        // conv to char16_t so we can read shorts when iterating
        const char16_t *ptr = reinterpret_cast<const char16_t *>(this->m_positionPtr);

        // poor man's strlen
        size_t len = 0;
        while (ptr[len] != 0) ++len;

        // read the string from buffer
        std::u16string result = readU16String(len, endian);

        // bump because we had to read null terminator
        this->m_positionPtr += sizeof(char16_t);
        return result;
    }

    std::u32string BinaryBuffer::readU32String(const size_t size,
                                               const util::ByteOrder endian) {
        std::u32string res(size, u'\0');

        readInto(reinterpret_cast<uint8_t *>(&res[0]), size * sizeof(char32_t));

#if defined(BR_BIG_ENDIAN)
        if (endian == util::ByteOrder::LITTLE) {
#else
        if (endian == util::ByteOrder::BIG) {
#endif
            for (char32_t &c: res) {
                c = util::ByteOrderUtil::swapOrder(c);
            }
        }

        return res;
    }

    std::u32string BinaryBuffer::readU32StringNT(const util::ByteOrder endian) {
        // conv to char16_t so we can read shorts when iterating
        const char32_t *ptr = reinterpret_cast<const char32_t *>(this->m_positionPtr);

        // poor man's strlen
        size_t len = 0;
        while (ptr[len] != 0) ++len;

        // read the string from buffer
        std::u32string result = readU32String(len, endian);

        // bump because we had to read null terminator
        this->m_positionPtr += sizeof(char32_t);
        return result;
    }

    void BinaryBuffer::writeString(const std::string &input, const bool nullTerminate) {
        writeBytes(reinterpret_cast<const uint8_t *>(input.data()),
                   input.size());

        if (nullTerminate)
            this->writeByte(0);
    }

    void BinaryBuffer::writeU16String(const std::u16string &input,
                                      const util::ByteOrder endian,
                                      const bool nullTerminate = false) {
        this->writeBytes(reinterpret_cast<const uint8_t *>(input.data()), input.size() * sizeof(char16_t));

        if (nullTerminate)
            this->write<char16_t>(0, endian);
    }

    void BinaryBuffer::writeU32String(const std::u32string &input,
                                      const util::ByteOrder endian,
                                      const bool nullTerminate = false) {
        this->writeBytes(reinterpret_cast<const uint8_t *>(input.data()), input.size() * sizeof(char32_t));

        if (nullTerminate)
            this->write<char32_t>(0, endian);
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

    io::ISeekable &BinaryBuffer::operator+=(const size_t amount) {
        this->m_positionPtr += amount;
        return *this;
    }

    io::ISeekable &BinaryBuffer::operator-=(const size_t amount) {
        this->m_positionPtr -= amount;
        return *this;
    }

    void BinaryBuffer::writeUint24(const uint32_t v, const bio::util::ByteOrder endian) {
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

    void BinaryBuffer::writeInt24(const int32_t v, const bio::util::ByteOrder endian) {
        writeUint24(static_cast<uint32_t>(v), endian);
    }
} // namespace lce::io
