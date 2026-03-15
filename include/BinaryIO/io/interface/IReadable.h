//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_IREADABLE_H
#define BIO_IREADABLE_H
#include "BinaryIO/io/Serializable.h"

#include <cstdint>
#include <stddef.h>
#include <string>
#include <vector>

#include "BinaryIO/util/ByteOrder.h"

#include <memory>

namespace bio {
    namespace io {
        namespace interface {
            /** Interface to provide reading methods
             *
             * If calls are a bit slow, it might help to fully qualify them.
             *
             * @code
             * IReadable *r = new SomeReadable();
             * r->SomeReadable::readByte(); // most compilers do this automatically
             * @endcode
             */
            class BIO_API IReadable {
            public:
                virtual ~IReadable() = default;

                /** Reads a value the size of the given type using the given endian/byte
                 * order
                 *
                 * @param endian The byte order to read as
                 * @returns The value
                 *
                 * @see readBE() for reading a Big Endian value
                 * @see readLE() for reading a Little Endian value
                 */
                template <typename T> T read(const util::ByteOrder endian);

                /** Reads a value the size of the given type as Little Endian
                 *
                 * @returns The value
                 *
                 * @see readBE() for reading a Big Endian value
                 */
                template <typename T> T readLE();

                /** Reads a value the size of the given type as Big Endian
                 *
                 * @returns The value
                 *
                 * @see readLE() for reading a Little Endian value
                 */
                template <typename T> T readBE();


                /** Reads a value the size of the given type using the platform endian/byte
                 * order
                 *
                 * @returns The value
                 *
                 * @see readBE() for reading a Big Endian value
                 * @see readLE() for reading a Little Endian value
                 */
                template <typename T> T read();

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
                virtual uint32_t readUint24();

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
                virtual int32_t readInt24();

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

                /** Reads a null terminated wide string
                 *
                 * @returns The string
                 */
                template <typename CharT, typename = std::enable_if_t<(sizeof(CharT) > 1)>>
                std::basic_string<CharT> readStringNullTerminated(util::ByteOrder endian);

                /** Reads a null terminated multibyte string
                 *
                 * @returns The string
                 */
                template <typename CharT, typename = std::enable_if_t<sizeof(CharT) == 1>>
                std::basic_string<CharT> readStringNullTerminated();

                /** Reads a byte */
                virtual IReadable &operator>>(uint8_t &b);
            };
        }
    }
}

#endif //BIO_IREADABLE_H
