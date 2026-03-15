//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_BINARYINPUTSTREAM_H
#define BIO_BINARYINPUTSTREAM_H
#include "BinaryIO/io/interface/ICanDeserialize.h"

#include <iosfwd>
#include <istream>
#include <vector>

#include "BinaryIO/io/interface/IReadable.h"
#include "BinaryIO/io/interface/ISeekable.h"
#include "BinaryIO/io/interface/ISimplePeekable.h"
#include "BinaryIO/util/ByteOrder.h"
#include "BinaryIO/util/ByteOrderUtil.h" //NOLINT (import is used by tpp file)
#include "BinaryIO/util/string/StringLengthEncoding.h"

namespace bio {
    namespace stream {
        // bis bos
        /** std::istream wrapper with added reading methods */
        class BIO_API BinaryInputStream : public io::interface::IReadable,
                                          public io::interface::ISimplePeekable,
                                          public io::interface::ISeekable, public io::interface::ICanDeserialize {
        public:
            explicit BinaryInputStream(std::istream &s);

            IMPLEMENT_DESERIALIZABLE()

            /** Reads a value the size of the given type using the given endian/byte
             * order
             *
             * @param endian The byte order to read as
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             * @see readLE() for reading a Little Endian value
             */
            template <typename T>
            T read(util::ByteOrder endian);

            /** Reads a value the size of the given type using the platform endian/byte
             * order
             *
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             * @see readLE() for reading a Little Endian value
             */
            template <typename T>
            T read();

            /** Reads a value the size of the given type as Little Endian
             *
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             */
            template <typename T>
            T readLE();

            /** Reads a value the size of the given type as Big Endian
             *
             * @returns The value
             *
             * @see readLE() for reading a Little Endian value
             */
            template <typename T>
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

            /** Reads a wide string with the given length
             *
             * @returns The string
             */
            template <typename CharT, typename = std::enable_if_t<(sizeof(CharT) > 1)>>
            std::basic_string<CharT> readString(size_t length, util::ByteOrder endian);

            /** Reads a multibyte string with the given length
             *
             * @returns The string
             */
            template <typename CharT, typename = std::enable_if_t<sizeof(CharT) == 1>>
            std::basic_string<CharT> readString(size_t length);

            /** Reads a string with an encoded length
             *
             * @note if you're providing @ref bio::util::string::StringLengthEncoding::NULL_TERMINATED for lengthEncoding, and CharT as char, then endian is not used.
             *
             * @param endian The endianness to read the chars and/or lengthEncoding as.
             * @param lengthEncoding The length encoding type.
             *
             * @returns The string
             */
            template <typename CharT>
            std::basic_string<CharT> readStringWithLength(util::ByteOrder endian, util::string::StringLengthEncoding lengthEncoding);

            /** Reads a char string that ends with a null terminator
             *
             * This is a wrapper around @ref readStringWithLength(util::ByteOrder endian, util::string::StringLengthEncoding lengthEncoding)
             */
            template <typename CharT, typename = std::enable_if_t<sizeof(CharT) == 1>>
            std::basic_string<CharT> readCharStringNullTerminated();

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
}

#endif //BIO_BINARYINPUTSTREAM_H
