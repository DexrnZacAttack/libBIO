//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_BINARYOUTPUTSTREAM_H
#define BIO_BINARYOUTPUTSTREAM_H
#include "BinaryIO/io/interface/ICanDeserialize.h"
#include "BinaryIO/io/interface/ICanSerialize.h"

#include <ostream>

#include "BinaryIO/io/interface/IWritable.h"
#include "BinaryIO/util/ByteOrderUtil.h"
#include "BinaryIO/io/interface/ISeekable.h"

namespace bio {
    namespace stream {
        /** std::ostream wrapper with added writing methods */
        class BIO_API BinaryOutputStream : public io::interface::IWritable,
                                           public io::interface::ISeekable, public io::interface::ICanSerialize {
        public:
            explicit BinaryOutputStream(std::ostream &s);

            IMPLEMENT_SERIALIZABLE()
            IMPLEMENT_DESERIALIZABLE()

            /** Writes a value with the given endianness
             *
             * @param v The value to write
             * @param endian The byte order to write that value in
             */
            template <typename T>
            void write(const T v, const util::ByteOrder endian);

            /** Writes a value with the platform endianness
             *
             * @param v The value to write
             */
            template <typename T>
            void write(const T v);

            /** Writes a value in Little Endian
             *
             * @param v The value to write
             */
            template <typename T>
            void writeLE(const T v);

            /** Writes a value in Big Endian
             *
             * @param v The value to write
             */
            template <typename T>
            void writeBE(const T v);

            void writeByte(uint8_t v) override;

            void writeSignedByte(int8_t v) override;

            void writeBytes(const uint8_t *v, size_t size) override;

            /** Writes a string
             *
             * @param input The input string
             * @param byteOrder The byte order for each char to be written with, if sizeof(CharT) is 1, this will be only used for writing the lengthEncoding
             * @param lengthEncoding The method in which we should encode the length alongside the string
             */
            template <typename CharT>
            void writeString(const platform::ReadableString<CharT> &input, util::ByteOrder byteOrder, util::string::StringLengthEncoding lengthEncoding);

            size_t getOffset() const override;

            void seek(size_t offset) override;

            void seekRelative(size_t offset) override;

            bool canSeek() const override;

            ISeekable &operator+=(size_t amount) override;

            ISeekable &operator-=(size_t amount) override;

            const std::ostream &getStream() const;

            std::ostream &getStream();

            void writeUint24(uint32_t v, bio::util::ByteOrder endian) override;

            void writeInt24(int32_t v, bio::util::ByteOrder endian) override;

            /** Writes `sz` amount of `b` bytes
             *
             * @param b The byte to fill with
             * @param sz How many bytes should be placed
             */
            void fill(uint8_t b, size_t sz);

        private:
            std::ostream &m_stream;

            bool m_isSeekable = false;
        };

#include "BinaryIO/stream/BinaryOutputStream.tpp"
    }
}

#endif //BIO_BINARYOUTPUTSTREAM_H
