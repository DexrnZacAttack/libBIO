//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/stream/BinaryInputStream.h"

namespace bio::stream {
    BinaryInputStream::BinaryInputStream(std::istream &s) : mStream(s) {
        mIsSeekable = s.tellg() != -1;
    }

    uint8_t BinaryInputStream::readByte() {
        char b;
        mStream.get(b);

        return static_cast<uint8_t>(b);
    }

    int8_t BinaryInputStream::readSignedByte() {
        char b;
        mStream.get(b);

        return static_cast<int8_t>(b);
    }

    uint32_t BinaryInputStream::readUint24(const bio::util::ByteOrder endian) {
        uint8_t medium[3];
        mStream.read(reinterpret_cast<char *>(medium), 3);

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

    int32_t BinaryInputStream::readInt24(const bio::util::ByteOrder endian) {
        uint32_t res = readUint24(endian);

        if (res & (1 << 23)) {
            res |= 0xFF000000;
        }

        return static_cast<int32_t>(res);
    }

    uint8_t *BinaryInputStream::readOfSize(const size_t sz) {
        uint8_t *out = new uint8_t[sz];
        mStream.read(reinterpret_cast<char *>(out), sz);

        return out;
    }

    std::vector<uint8_t> BinaryInputStream::readOfSizeVec(const size_t sz) {
        std::vector<uint8_t> out(sz);
        mStream.read(reinterpret_cast<char *>(out.data()), sz);

        return out;
    }

    void BinaryInputStream::readInto(uint8_t *into, const size_t sz) {
        mStream.read(reinterpret_cast<char *>(into), sz);
    }

    size_t BinaryInputStream::getPosition() const {
        return mStream.tellg();
    }

    void BinaryInputStream::seek(const size_t offset) {
        mStream.seekg(offset);
    }

    void BinaryInputStream::seekRelative(const size_t offset) {
        mStream.seekg(offset, std::ios::cur);
    }

    bool BinaryInputStream::canSeek() const {
        return mIsSeekable;
    }

    std::string BinaryInputStream::readString(const size_t size) {
        std::string result(size, '\0');
        readInto(reinterpret_cast<uint8_t *>(result.data()), size);

        return result;
    }

    std::string BinaryInputStream::readStringNT() {
        std::string res;

        char c;
        while (mStream.get(c)) {
            if (c == '\0') break;
            res += c;
        }

        return res;
    }

    std::u16string BinaryInputStream::readU16String(const size_t size, const bio::util::ByteOrder endian) {
        std::u16string res(size, u'\0');

        readInto(reinterpret_cast<uint8_t *>(res.data()), size * sizeof(char16_t));

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

    std::u16string BinaryInputStream::readU16StringNT(const bio::util::ByteOrder endian) {
        std::u16string res;

        char16_t c = u'\00';
        while (true) {
            c = read<char16_t>(endian);

            if (c == u'\00') break;

            res += c;
        }

#if defined(BR_BIG_ENDIAN)
        if (endian == util::ByteOrder::LITTLE) {
#else
        if (endian == util::ByteOrder::BIG) {
#endif
            for (char16_t &cc: res) {
                cc = util::ByteOrderUtil::swapOrder(cc);
            }
        }

        return res;
    }

    std::u32string BinaryInputStream::readU32String(const size_t size, const bio::util::ByteOrder endian) {
        std::u32string res(size, U'\0');

        readInto(reinterpret_cast<uint8_t *>(res.data()), size * sizeof(char32_t));

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

    std::u32string BinaryInputStream::readU32StringNT(const bio::util::ByteOrder endian) {
        std::u32string res;

        char32_t c = U'\00';
        while (true) {
            c = read<char32_t>(endian);

            if (c == U'\00') break;

            res += c;
        }

#if defined(BR_BIG_ENDIAN)
        if (endian == util::ByteOrder::LITTLE) {
#else
        if (endian == util::ByteOrder::BIG) {
#endif
            for (char32_t &cc: res) {
                cc = util::ByteOrderUtil::swapOrder(cc);
            }
        }

        return res;
    }

    util::ISeekable &BinaryInputStream::operator+=(const size_t amount) {
        seekRelative(amount);
        return *this;
    }

    util::ISeekable &BinaryInputStream::operator-=(const size_t amount) {
        seekRelative(amount);
        return *this;
    }

    const std::istream &BinaryInputStream::getStream() const {
        return mStream;
    }

    std::istream &BinaryInputStream::getStream() {
        return mStream;
    }
}
