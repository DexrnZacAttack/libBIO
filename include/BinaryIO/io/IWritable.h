//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_IWRITABLE_H
#define BIO_IWRITABLE_H
#include <cstdint>
#include <stddef.h>
#include <string>

#include "BinaryIO/util/ByteOrder.h"

namespace bio::io {
    /** Interface to provide writing methods
     *
     * If calls are a bit slow, it might help to fully qualify them.
     *
     * @code
     * IWritable *w = new SomeWritable();
     * w->SomeWritable::writeByte(0x00); // most compilers do this automatically
     * @endcode
     */
    class BIO_API IWritable {
    public:
        virtual ~IWritable() = default;

        /** Writes a byte */
        virtual void writeByte(uint8_t v) = 0;

        /** Writes a signed byte */
        virtual void writeSignedByte(int8_t v) = 0;

        /** Writes an array of bytes */
        virtual void writeBytes(const uint8_t *v, size_t size) = 0;

        /** Writes a char string
         *
         * @param input The input string
         * @param nullTerminate Whether to end the string with a null byte
         */
        virtual void writeString(const std::string &input, bool nullTerminate) = 0;

        /** Writes a char16_t string
         *
         * @param input The input string
         * @param endian The byte order to write each char in
         * @param nullTerminate Whether to end the string with a null byte
         */
        virtual void writeU16String(const std::u16string &input, bio::util::ByteOrder endian,
                     bool nullTerminate) = 0;

        /** Writes a char32_t string
         *
         * @param input The input string
         * @param endian The byte order to write each char in
         * @param nullTerminate Whether to end the string with a null byte
         */
        virtual void writeU32String(const std::u32string &input, bio::util::ByteOrder endian,
                             bool nullTerminate) = 0;

        /** Writes a byte */
        virtual IWritable& operator<<(uint8_t b);
    };
}

#endif //BIO_IWRITABLE_H