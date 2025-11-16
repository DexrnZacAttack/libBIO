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
                                            bool nullTerminate) {
        this->writeBytes(reinterpret_cast<const uint8_t *>(input.data()), input.size() * sizeof(char16_t));

        if (nullTerminate)
            this->write<char16_t>(0, endian);
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
}
