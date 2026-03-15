//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/stream/BinaryOutputStream.h"

#include <ostream>

namespace bio {
    namespace stream {
        BinaryOutputStream::BinaryOutputStream(std::ostream &s) : m_stream(s) {
            m_isSeekable = s.tellp() != -1;
        }

        void BinaryOutputStream::writeByte(const uint8_t v) {
            m_stream << v;
        }

        void BinaryOutputStream::writeSignedByte(const int8_t v) {
            m_stream << v;
        }

        void BinaryOutputStream::writeBytes(const uint8_t *v,
                                            const size_t size) {
            m_stream.write(reinterpret_cast<const char *>(v), size);
        }

        size_t BinaryOutputStream::getOffset() const {
            return m_stream.tellp();
        }

        void BinaryOutputStream::seek(const size_t offset) {
            m_stream.seekp(offset);
        }

        void BinaryOutputStream::seekRelative(const size_t offset) {
            m_stream.seekp(offset, std::ios::cur);
        }

        bool BinaryOutputStream::canSeek() const {
            return m_isSeekable;
        }

        io::interface::ISeekable &BinaryOutputStream::operator+=(const size_t amount) {
            seekRelative(amount);
            return *this;
        }

        io::interface::ISeekable &BinaryOutputStream::operator-=(const size_t amount) {
            seekRelative(amount);
            return *this;
        }

        const std::ostream &BinaryOutputStream::getStream() const {
            return m_stream;
        }

        std::ostream &BinaryOutputStream::getStream() {
            return m_stream;
        }

        void BinaryOutputStream::writeUint24(const uint32_t v,
                                             const bio::util::ByteOrder
                                             endian) {
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

        void BinaryOutputStream::writeInt24(const int32_t v,
                                            const bio::util::ByteOrder endian) {
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
}
