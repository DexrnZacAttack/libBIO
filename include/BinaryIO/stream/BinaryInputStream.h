//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_BINARYINPUTSTREAM_H
#define BIO_BINARYINPUTSTREAM_H
#include <iosfwd>
#include <istream>
#include <vector>

#include "BinaryIO/io/IReadable.h"
#include "BinaryIO/util/ByteOrder.h"
#include "BinaryIO/io/ISeekable.h"
#include "BinaryIO/io/ISimplePeekable.h"
#include "BinaryIO/util/ByteOrderUtil.h" //NOLINT (import is used by tpp file)

namespace bio::stream {
    // bis bos
    /** std::istream wrapper with added reading methods */
    class BIO_API BinaryInputStream : public io::IReadable, public io::ISimplePeekable, public io::ISeekable {
    public:
        explicit BinaryInputStream(std::istream &s);

        /** Reads a value the size of the given type using the given endian/byte
         * order
         *
         * @param endian The byte order to read as
         * @returns The value
         *
         * @see readBE() for reading a Big Endian value
         * @see readLE() for reading a Little Endian value
         */
        template<typename T>
        T read(util::ByteOrder endian);

        /** Reads a value the size of the given type as Little Endian
         *
         * @returns The value
         *
         * @see readBE() for reading a Big Endian value
         */
        template<typename T>
        T readLE();

        /** Reads a value the size of the given type as Big Endian
         *
         * @returns The value
         *
         * @see readLE() for reading a Little Endian value
         */
        template<typename T>
        T readBE();

        uint8_t peekByte() const override;

        int8_t peekSignedByte() const override;

        uint8_t readByte() override;

        int8_t readSignedByte() override;

        uint32_t readUint24(bio::util::ByteOrder endian) override;

        int32_t readInt24(bio::util::ByteOrder endian) override;

        uint8_t *readOfSize(size_t sz) override;

        std::vector<uint8_t> readOfSizeVec(size_t sz) override;

        void readInto(uint8_t *into, size_t sz) override;

        size_t getOffset() const override;

        void seek(size_t offset) override;

        void seekRelative(size_t offset) override;

        bool canSeek() const override;

        std::string readString(size_t size) override;

        std::string readStringNT() override;

        std::u16string readU16String(size_t size, bio::util::ByteOrder endian) override;

        std::u16string readU16StringNT(bio::util::ByteOrder endian) override;

        std::u32string readU32String(size_t size, bio::util::ByteOrder endian) override;

        std::u32string readU32StringNT(bio::util::ByteOrder endian) override;

        ISeekable &operator+=(size_t amount) override;

        ISeekable &operator-=(size_t amount) override;

        const std::istream &getStream() const;

        std::istream &getStream();

    private:
        std::istream &m_stream;

        bool m_isSeekable = false;
    };

#include "BinaryIO/stream/BinaryInputStream.tpp"
}

#endif //BIO_BINARYINPUTSTREAM_H
