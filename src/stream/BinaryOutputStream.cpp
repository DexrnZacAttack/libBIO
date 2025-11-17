//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/stream/BinaryOutputStream.h"

#include <ostream>

namespace bio::stream {
    BinaryOutputStream::BinaryOutputStream(std::ostream &s) : mStream(s) {
        mIsSeekable = s.tellp() != -1;
    }

    void BinaryOutputStream::writeByte(const uint8_t v) {
        mStream << v;
    }

    void BinaryOutputStream::writeSignedByte(const int8_t v) {
        mStream << v;
    }

    void BinaryOutputStream::writeBytes(const uint8_t *v, const size_t size) {
        mStream.write(reinterpret_cast<const char *>(v), size);
    }

    void BinaryOutputStream::writeString(const std::string &input, const bool nullTerminate) {
        writeBytes(reinterpret_cast<const uint8_t *>(input.data()),
                   input.size());

        if (nullTerminate)
            this->writeByte(0);
    }

    void BinaryOutputStream::writeU16String(const std::u16string &input, const bio::util::ByteOrder endian,
                                            const bool nullTerminate) {
        this->writeBytes(reinterpret_cast<const uint8_t *>(input.data()), input.size() * sizeof(char16_t));

        if (nullTerminate)
            this->write<char16_t>(0, endian);
    }

    void BinaryOutputStream::writeU32String(const std::u32string &input, const bio::util::ByteOrder endian,
        const bool nullTerminate) {
        this->writeBytes(reinterpret_cast<const uint8_t *>(input.data()), input.size() * sizeof(char32_t));

        if (nullTerminate)
            this->write<char32_t>(0, endian);
    }

    size_t BinaryOutputStream::getPosition() const {
        return mStream.tellp();
    }

    void BinaryOutputStream::seek(const size_t offset) {
        mStream.seekp(offset);
    }

    void BinaryOutputStream::seekRelative(const size_t offset) {
        mStream.seekp(offset, std::ios::cur);
    }

    bool BinaryOutputStream::canSeek() const {
        return mIsSeekable;
    }

    util::ISeekable &BinaryOutputStream::operator+=(const size_t amount) {
        seekRelative(amount);
        return *this;
    }

    util::ISeekable &BinaryOutputStream::operator-=(const size_t amount) {
        seekRelative(amount);
        return *this;
    }

    const std::ostream & BinaryOutputStream::getStream() const {
        return mStream;
    }

    std::ostream & BinaryOutputStream::getStream() {
        return mStream;
    }

    void BinaryOutputStream::writeUint24(const uint32_t v, const bio::util::ByteOrder endian) {
        // Probably not the most efficient
        const uint8_t b0 = static_cast<uint8_t>(v & 0xFF);
        const uint8_t b1 = static_cast<uint8_t>((v >> 8) & 0xFF);
        const uint8_t b2 = static_cast<uint8_t>((v >> 16) & 0xFF);

        if (endian == util::ByteOrder::LITTLE) {
            writeByte(b0);
            writeByte(b1);
            writeByte(b2);
        } else {
            writeByte(b2);
            writeByte(b1);
            writeByte(b0);
        }
    }

    void BinaryOutputStream::writeInt24(const int32_t v, const bio::util::ByteOrder endian) {
        writeUint24(static_cast<uint32_t>(v), endian);
    }

    void BinaryOutputStream::fill(const uint8_t b, const size_t sz) {
        // Unsure if this is the fastest way, but should work fine.
        uint8_t *v = new uint8_t[sz];
        std::fill_n(v, sz, b);

        writeBytes(v, sz);

        delete[] v;
    }
}
