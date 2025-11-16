//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_IREADABLE_H
#define BIO_IREADABLE_H
#include <cstdint>
#include <stddef.h>
#include <string>
#include <vector>

#include "BinaryIO/util/ByteOrder.h"

namespace bio::io {
    /** Interface to provide reading methods
     *
     * If calls are a bit slow, it might help to fully qualify them.
     *
     * @code
     * IReadable *r = new SomeReadable();
     * r->SomeReadable::readByte(); // most compilers do this automatically
     * @endcode
     */
    class IReadable {
    public:
        virtual ~IReadable() = default;

        /** Reads an unsigned byte (uint8_t)
         *
         * @returns The byte
         *
         * @see readSignedByte() for reading a signed byte
         */
        virtual uint8_t readByte() = 0;
        /** Reads a signed byte (int8_t)
         *
         * @returns The signed byte
         *
         * @see readByte() for reading an unsigned byte
         */
        virtual int8_t readSignedByte() = 0;

        /** Reads an unsigned 24-bit integer
         *
         * @returns The unsigned 24-bit integer
         *
         * @see readInt24() for reading a signed 24-bit integer
         */
        virtual uint32_t readUint24(bio::util::ByteOrder endian) = 0;

        /** Reads a signed 24-bit integer
         *
         * @returns The signed 24-bit integer
         *
         * @see readInt24() for reading an unsigned 24-bit integer
         */
        virtual int32_t readInt24(bio::util::ByteOrder endian) = 0;

        /** Reads `sz` amount of bytes into a new byte array
         *
         * @param sz The amount to read
         */
        virtual uint8_t *readOfSize(size_t sz) = 0;

        /** Reads `sz` amount of bytes into a new vector
         *
         * @param sz The amount to read
         */
        virtual std::vector<uint8_t> readOfSizeVec(size_t sz) = 0;

        /** Reads `sz` amount of bytes into a given byte array
         *
         * @param into The array to read into
         * @param sz The amount to read
         */
        virtual void readInto(uint8_t *into, size_t sz) = 0;

        /** Reads a char string of given size
         *
         * @param size The total size in bytes of the string that you want to read
         * @returns The string
         */
        virtual std::string readString(size_t size) = 0;

        /** Reads a null terminated string
         *
         * @returns The string
         */
        virtual std::string readStringNT() = 0;

        /** Reads a char16 string of given size
         *
         * @param size The total size in char16s of the string that you want to read
         * @param endian The endianness of the string being read from buffer, this will be converted to the system's native endian.
         *
         * @returns The string
         */
        virtual std::u16string readU16String(size_t size, bio::util::ByteOrder endian) = 0;

        /** Reads a null terminated char16 string
         *
         * @param endian The endianness of the string being read from buffer, this will be converted to the system's native endian.
         *
         * @returns The string
         */
        virtual std::u16string readU16StringNT(bio::util::ByteOrder endian) = 0;

        /** Reads a char32 string of given size
         *
         * @param size The total size in char32s of the string that you want to read
         * @param endian The endianness of the string being read from buffer, this will be converted to the system's native endian.
         *
         * @returns The string
         */
        virtual std::u32string readU32String(size_t size, bio::util::ByteOrder endian) = 0;

        /** Reads a null terminated char32 string
         *
         * @param endian The endianness of the string being read from buffer, this will be converted to the system's native endian.
         *
         * @returns The string
         */
        virtual std::u32string readU32StringNT(bio::util::ByteOrder endian) = 0;

        /** Reads a byte */
        virtual IReadable& operator>>(uint8_t &b);
    };
}

#endif //BIO_IREADABLE_H
