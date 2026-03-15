//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_IWRITABLE_H
#define BIO_IWRITABLE_H
#include "BinaryIO/io/Serializable.h"

#include <cstdint>
#include <stddef.h>
#include "BinaryIO/Platform.h"

#include "BinaryIO/util/ByteOrder.h"
#include "BinaryIO/util/string/StringLengthEncoding.h"

namespace bio {
    namespace io {
        namespace interface {
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
                template <typename T> void writeLE(const T v);

                /** Writes a value in Big Endian
                 *
                 * @param v The value to write
                 */
                template <typename T> void writeBE(const T v);

                /** Writes a byte */
                virtual void writeByte(uint8_t v) = 0;

                /** Writes a signed byte */
                virtual void writeSignedByte(int8_t v) = 0;

                /** Writes an uint24 (unsigned 3 byte int) */
                virtual void writeUint24(uint32_t v);

                /** Writes an uint24 (unsigned 3 byte int) */
                virtual void writeUint24(uint32_t v, bio::util::ByteOrder endian) =
                0;

                /** Writes an int24 (signed 3 byte int) */
                virtual void writeInt24(int32_t v);

                /** Writes an int24 (signed 3 byte int) */
                virtual void writeInt24(int32_t v, bio::util::ByteOrder endian) = 0;

                /** Writes an array of bytes */
                virtual void writeBytes(const uint8_t *v, size_t size) = 0;

                /** Writes a string
                 *
                 * @param input The input string
                 * @param byteOrder The byte order for each char to be written with, if sizeof(CharT) is 1, this will be only used for writing the lengthEncoding
                 * @param lengthEncoding The method in which we should encode the length alongside the string
                 */
                template <typename CharT>
                void writeString(const platform::ReadableString<CharT> &input, util::ByteOrder byteOrder, util::string::StringLengthEncoding lengthEncoding);

                /** Writes a byte */
                virtual IWritable &operator<<(uint8_t b);
            };
        }
    }
}

#endif //BIO_IWRITABLE_H