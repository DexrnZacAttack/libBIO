//
// Created by (Person who prefers not to be named) and DexrnZacAttack on
// 20/12/2024.
//

#ifndef BINARYIO_H
#define BINARYIO_H

#include <cstdint>
#include <string>
#include <vector>

#include "BinaryIO/Library.h"
#include "io/IReadable.h"
#include "io/IWritable.h"
#include "util/ByteOrder.h"
#include "util/ByteOrderUtil.h"
#include "util/ISeekable.h"

namespace bio {
    /** Unsized reader/writer for a byte array */
    class BIO_API BinaryBuffer final : public io::IReadable, public io::IWritable, public util::ISeekable {
      public:
        explicit BinaryBuffer(uint8_t *input);
        explicit BinaryBuffer(size_t size);

        // ~BinaryIO();

        void seek(size_t offset) override;
        void seekRelative(size_t offset) override;

        bool canSeek() const override;

        // reading
        /** Reads a value the size of the given type using the given endian/byte
         * order
         *
         * @param endian The byte order to read as
         * @returns The value
         *
         * @see readBE() for reading a Big Endian value
         * @see readLE() for reading a Little Endian value
         */
        template <typename T> T read(const util::ByteOrder endian) {
            if (endian == bio::util::ByteOrder::LITTLE) return readLE<T>();

            return readBE<T>();
        }

        /** Reads a value the size of the given type as Little Endian
         *
         * @returns The value
         *
         * @see readBE() for reading a Big Endian value
         */
        template <typename T> T readLE() {
            const T v = util::ByteOrderUtil::little2sys(*reinterpret_cast<const T *>(this->mData));
            this->mData += sizeof(T);
            return v;
        }

        /** Reads a value the size of the given type as Big Endian
         *
         * @returns The value
         *
         * @see readLE() for reading a Little Endian value
         */
        template <typename T> T readBE() {
            const T v = util::ByteOrderUtil::big2sys(*reinterpret_cast<const T *>(this->mData));
            this->mData += sizeof(T);
            return v;
        }

        uint8_t readByte() override;

        int8_t readSignedByte() override;

        uint32_t readUint24(util::ByteOrder endian) override;

        int32_t readInt24(util::ByteOrder endian) override;

        uint8_t * readOfSize(size_t sz) override;

        std::vector<uint8_t> readOfSizeVec(size_t sz) override;

        void readInto(uint8_t *into, size_t sz) override;

        // writing
        /** Writes a value with the given endianness
         *
         * @param v The value to write
         * @param endian The byte order to write that value in
         */
        template <typename T>
        void write(const T v, const util::ByteOrder endian) {
            if (endian == util::ByteOrder::LITTLE)
                *reinterpret_cast<T *>(this->mData) = util::ByteOrderUtil::little2sys(v);
            else
                *reinterpret_cast<T *>(this->mData) = util::ByteOrderUtil::big2sys(v);
            this->mData += sizeof(T);
        }

        /** Writes a value in Little Endian
         *
         * @param v The value to write
         */
        template <typename T> void writeLE(const T v) {
            *reinterpret_cast<T *>(this->mData) = util::ByteOrderUtil::little2sys(v);
            this->mData += sizeof(T);
        }

        /** Writes a value in Big Endian
         *
         * @param v The value to write
         */
        template <typename T> void writeBE(const T v) {
            *reinterpret_cast<T *>(this->mData) = util::ByteOrderUtil::big2sys(v);
            this->mData += sizeof(T);
        }

        uint8_t *getData() const;

        uint8_t *getDataRelative() const;

        size_t getPosition() const override;

        void writeByte(uint8_t v) override;

        void writeSignedByte(int8_t v) override;

        void writeBytes(const uint8_t *v, size_t size) override;

        std::string readString(size_t size) override;

        std::string readStringNT() override;

        std::u16string readU16String(size_t size, util::ByteOrder endian) override;

        std::u16string readU16StringNT(util::ByteOrder endian) override;

        std::u32string readU32String(size_t size, util::ByteOrder endian) override;

        std::u32string readU32StringNT(util::ByteOrder endian) override;

        void writeString(const std::string &input, bool nullTerminate) override;

        void writeU16String(const std::u16string &input, util::ByteOrder endian, bool nullTerminate) override;

        void writeU32String(const std::u32string &input, util::ByteOrder endian, bool nullTerminate) override;

        /** Returns a byte at the given offset */
        uint8_t& operator[](size_t i);

        /** Returns a byte at the given offset */
        const uint8_t& operator[](size_t i) const;

        ISeekable & operator+=(size_t amount) override;

        ISeekable & operator-=(size_t amount) override;

        void writeUint24(uint32_t v, bio::util::ByteOrder endian) override;

        void writeInt24(int32_t v, bio::util::ByteOrder endian) override;

    private:
        uint8_t *mOrigin; /**< Data origin */
        uint8_t *mData;   /**< Data pointer, holds where we are in the array */
    };
} // namespace lce::io

#endif // BINARYIO_H
