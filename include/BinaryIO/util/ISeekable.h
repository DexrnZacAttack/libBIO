//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_BINARYSTREAM_H
#define BIO_BINARYSTREAM_H

#include "BinaryIO/Library.h"
#include <stddef.h> // why won't it find size_t otherwise

namespace bio::util {
    /** Interface for a seekable buffer/stream */
    class BIO_API ISeekable {
    public:
        virtual ~ISeekable() = default;

        /** Returns the current position in the buffer */
        virtual size_t getPosition() const = 0;

        /** Seeks to a certain position in the buffer */
        virtual void seek(size_t offset) = 0;
        /** Seeks to a certain position in the buffer based off the current position */
        virtual void seekRelative(size_t offset) = 0;
        /** Checks if the buffer is seekable
         *
         * @return `true` if we can seek
         */
        virtual bool canSeek() const = 0;

        /** Increments the offset by the given amount */
        virtual ISeekable& operator+=(size_t amount) = 0;
        /** Decrements the offset by the given amount */
        virtual ISeekable& operator-=(size_t amount) = 0;
    };
}

#endif //BIO_BINARYSTREAM_H
