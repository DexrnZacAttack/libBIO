//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_IPEEKABLE_H
#define BIO_IPEEKABLE_H
#include "BinaryIO/io/ISimplePeekable.h"

#include <cstdint>
#include <stddef.h>
#include <string>
#include <vector>

#include "BinaryIO/util/ByteOrder.h"
#include "BinaryIO/util/Origin.h"

namespace bio::io {
    /** Interface to provide peeking methods
     *
     * Peeking allows you to read at an offset, without incrementing the internal position pointer,
     * not incrementing the internal position ptr allows these methods to be @c const.
     *
     * If calls are a bit slow, it might help to fully qualify them.
     *
     * @code
     * IPeekable *r = new SomePeekable();
     * r->SomePeekable::peekByte(); // most compilers do this automatically
     * @endcode
     */
    class BIO_API IPeekable {
    public:
        virtual ~IPeekable() = default;

        /** Peeks at an unsigned byte (uint8_t)
         *
         * Peeking does not increment the position
         *
         * @param origin Origin to add the offset to
         * @param offset The offset to read from
         *
         * @returns The byte
         *
         * @see peekSignedByte() for peeking a signed byte
         */
        virtual uint8_t peekByte(util::Origin origin, size_t offset = 0) const = 0;

        /** Peeks a signed byte (int8_t)
         *
         * Peeking does not increment the position
         *
         * @param origin Origin to add the offset to
         * @param offset The offset to read from
         *
         * @returns The signed byte
         *
         * @see peekByte() for peeking an unsigned byte
         */
        virtual int8_t peekSignedByte(util::Origin origin, size_t offset = 0) const = 0;

        /** Peeks an unsigned 24-bit integer
         *
         * Peeking does not increment the position
         *
         * @param endian The byte order to read as
         * @param origin Origin to add the offset to
         * @param offset The offset to read from
         *
         * @returns The unsigned 24-bit integer
         *
         * @see peekInt24() for peeking a signed 24-bit integer
         */
        virtual uint32_t peekUint24(bio::util::ByteOrder endian, util::Origin origin, size_t offset = 0) const = 0;

        /** Peeks a signed 24-bit integer
         *
         * Peeking does not increment the position
         *
         * @param endian The byte order to read as
         * @param origin Origin to add the offset to
         * @param offset The offset to read from
         *
         * @returns The signed 24-bit integer
         *
         * @see peekInt24() for peeking an unsigned 24-bit integer
         */
        virtual int32_t peekInt24(bio::util::ByteOrder endian, util::Origin origin, size_t offset = 0) const = 0;

        /** Reads `sz` amount of bytes into a new byte array
         *
         * Peeking does not increment the position
         *
         * @param sz The amount to read
         * @param origin Origin to add the offset to
         * @param offset The offset to read from
         */
        virtual uint8_t *peekOfSize(size_t sz, util::Origin origin, size_t offset = 0) const = 0;

        /** Reads `sz` amount of bytes into a new vector
         *
         * Peeking does not increment the position
         *
         * @param sz The amount to read
         * @param origin Origin to add the offset to
         * @param offset The offset to read from
         */
        virtual std::vector<uint8_t> peekOfSizeVec(size_t sz, util::Origin origin, size_t offset = 0) const = 0;

        /** Reads `sz` amount of bytes into a given byte array
         *
         * Peeking does not increment the position
         *
         * @param into The array to read into
         * @param sz The amount to read
         * @param origin Origin to add the offset to
         * @param offset The offset to read from
         */
        virtual void peekInto(uint8_t *into, size_t sz, util::Origin origin, size_t offset = 0) const = 0;
    };
}

#endif //BIO_IREADABLE_H
