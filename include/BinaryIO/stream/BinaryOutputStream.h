//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_BINARYOUTPUTSTREAM_H
#define BIO_BINARYOUTPUTSTREAM_H
#include <ostream>

#include "BinaryIO/io/IWritable.h"
#include "BinaryIO/util/ByteOrderUtil.h"
#include "BinaryIO/util/ISeekable.h"

namespace bio::stream {
    /** std::ostream wrapper with added writing methods */
    class BIO_API BinaryOutputStream : public io::IWritable, public util::ISeekable {
    public:
        BinaryOutputStream(std::ostream &s);

        /** Writes a value with the given endianness
         *
         * @param v The value to write
         * @param endian The byte order to write that value in
         */
        template<typename T>
        void write(const T v, const util::ByteOrder endian) {
            if (endian == util::ByteOrder::LITTLE) this->writeLE(v);
            else this->writeBE(v);
        }

        /** Writes a value in Little Endian
         *
         * @param v The value to write
         */
        template<typename T>
        void writeLE(const T v) {
            T c = util::ByteOrderUtil::little2sys(v);
            mStream.write(reinterpret_cast<char *>(&c), sizeof(v));
        }

        /** Writes a value in Big Endian
         *
         * @param v The value to write
         */
        template<typename T>
        void writeBE(const T v) {
            T c = util::ByteOrderUtil::big2sys(v);
            mStream.write(reinterpret_cast<char *>(&c), sizeof(v));
        }

        void writeByte(uint8_t v) override;

        void writeSignedByte(int8_t v) override;

        void writeBytes(const uint8_t *v, size_t size) override;

        void writeString(const std::string &input, bool nullTerminate) override;

        void writeU16String(const std::u16string &input, bio::util::ByteOrder endian, bool nullTerminate) override;

        void writeU32String(const std::u32string &input, bio::util::ByteOrder endian, bool nullTerminate) override;

        size_t getPosition() const override;

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
        std::ostream &mStream;

        bool mIsSeekable = false;
    };
}

#endif //BIO_BINARYOUTPUTSTREAM_H
