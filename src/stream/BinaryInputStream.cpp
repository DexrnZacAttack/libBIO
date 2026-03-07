//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/stream/BinaryInputStream.h"

namespace bio::stream {
    BinaryInputStream::BinaryInputStream(std::istream &s) : m_stream(s) {
        m_isSeekable = s.tellg() != -1;
    }

    uint8_t BinaryInputStream::peekByte() const {
        return this->m_stream.peek();
    }

    int8_t BinaryInputStream::peekSignedByte() const {
        return this->peekByte();
    }

    uint8_t BinaryInputStream::readByte() {
        char b;
        m_stream.get(b);

        return static_cast<uint8_t>(b);
    }

    int8_t BinaryInputStream::readSignedByte() {
        char b;
        m_stream.get(b);

        return static_cast<int8_t>(b);
    }

    uint32_t BinaryInputStream::readUint24(const bio::util::ByteOrder endian) {
        uint8_t medium[3];
        m_stream.read(reinterpret_cast<char *>(medium), 3);

        uint32_t v;
        if (endian == util::ByteOrder::LITTLE) {
            v = static_cast<uint32_t>(medium[0]) |
                (static_cast<uint32_t>(medium[1]) << 8) |
                (static_cast<uint32_t>(medium[2]) << 16);
        } else {
            v = (static_cast<uint32_t>(medium[0]) << 16) |
                (static_cast<uint32_t>(medium[1]) << 8) |
                static_cast<uint32_t>(medium[2]);
        }

        return v;
    }

    int32_t BinaryInputStream::readInt24(const util::ByteOrder endian) {
        uint32_t res = readUint24(endian);

        if (res & (1 << 23)) {
            res |= 0xFF000000;
        }

        return static_cast<int32_t>(res);
    }

    uint8_t *BinaryInputStream::readOfSize(const size_t sz) {
        uint8_t *out = new uint8_t[sz];
        m_stream.read(reinterpret_cast<char *>(out), sz);

        return out;
    }

    std::vector<uint8_t> BinaryInputStream::readOfSizeVec(const size_t sz) {
        std::vector<uint8_t> out(sz);
        m_stream.read(reinterpret_cast<char *>(out.data()), sz);

        return out;
    }

    void BinaryInputStream::readInto(uint8_t *into, const size_t sz) {
        m_stream.read(reinterpret_cast<char *>(into), sz);
    }

    size_t BinaryInputStream::getOffset() const {
        return m_stream.tellg();
    }

    void BinaryInputStream::seek(const size_t offset) {
        m_stream.seekg(offset);
    }

    void BinaryInputStream::seekRelative(const size_t offset) {
        m_stream.seekg(offset, std::ios::cur);
    }

    bool BinaryInputStream::canSeek() const {
        return m_isSeekable;
    }

    std::string BinaryInputStream::readString(const size_t size) {
        std::string result(size, '\0');
        readInto(reinterpret_cast<uint8_t *>(&result[0]), size);

        return result;
    }

    std::string BinaryInputStream::readStringNT() {
        std::string res;

        char c;
        while (m_stream.get(c)) {
            if (c == '\0') break;
            res += c;
        }

        return res;
    }

    std::u16string BinaryInputStream::readU16String(const size_t size, const bio::util::ByteOrder endian) {
        std::u16string res(size, u'\0');

        readInto(reinterpret_cast<uint8_t *>(&res[0]), size * sizeof(char16_t));

        if (endian != util::ByteOrder::PLATFORM) {
            for (char16_t &c: res) {
                c = util::ByteOrderUtil::swapOrder(c);
            }
        }

        return res;
    }

    std::u16string BinaryInputStream::readU16StringNT(const bio::util::ByteOrder endian) {
        std::u16string res;

        char16_t c = u'\00';
        while (true) {
            c = read<char16_t>(endian);

            if (c == u'\00') break;

            res += c;
        }

        if (endian != util::ByteOrder::PLATFORM) {
            for (char16_t &cc: res) {
                cc = util::ByteOrderUtil::swapOrder(cc);
            }
        }

        return res;
    }

    std::u32string BinaryInputStream::readU32String(const size_t size, const bio::util::ByteOrder endian) {
        std::u32string res(size, U'\0');

        readInto(reinterpret_cast<uint8_t *>(&res[0]), size * sizeof(char32_t));

        if (endian != util::ByteOrder::PLATFORM) {
            for (char32_t &c: res) {
                c = util::ByteOrderUtil::swapOrder(c);
            }
        }

        return res;
    }

    std::u32string BinaryInputStream::readU32StringNT(const bio::util::ByteOrder endian) {
        std::u32string res;

        char32_t c = U'\00';
        while (true) {
            c = read<char32_t>(endian);

            if (c == U'\00') break;

            res += c;
        }

        if (endian != util::ByteOrder::PLATFORM) {
            for (char32_t &cc: res) {
                cc = util::ByteOrderUtil::swapOrder(cc);
            }
        }

        return res;
    }

    io::ISeekable &BinaryInputStream::operator+=(const size_t amount) {
        seekRelative(amount);
        return *this;
    }

    io::ISeekable &BinaryInputStream::operator-=(const size_t amount) {
        seekRelative(amount);
        return *this;
    }

    const std::istream &BinaryInputStream::getStream() const {
        return m_stream;
    }

    std::istream &BinaryInputStream::getStream() {
        return m_stream;
    }
}
