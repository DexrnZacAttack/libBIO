//
// Created by DexrnZacAttack on 3/6/26 using zPc-i2.
//
#ifndef BIO_ISIMPLEPEEKABLE_H
#define BIO_ISIMPLEPEEKABLE_H
#include "BinaryIO/util/Origin.h"

#include <cstdint>

namespace bio {
    namespace io {
        namespace interface {
            /** Interface to provide simple peeking methods, mainly used for streams
             *
             * Peeking allows you to read a byte, without incrementing the position,
             * which allows these methods to be @c const.
             *
             * If calls are a bit slow, it might help to fully qualify them.
             *
             * @code
             * ISimplePeekable *r = new SomeSimplePeekable();
             * r->SomeSimplePeekable::peekByte(); // most compilers do this automatically
             * @endcode
             */
            class ISimplePeekable {
            public:
                virtual ~ISimplePeekable() = default;

                /** Peeks at the next unsigned byte (uint8_t)
                 *
                 * Peeking does not increment the position
                 *
                 * @returns The byte
                 *
                 * @see peekSignedByte() for peeking a signed byte
                 */
                virtual uint8_t peekByte() const = 0;

                /** Peeks at the next signed byte (int8_t)
                 *
                 * Peeking does not increment the position
                 *
                 * @returns The signed byte
                 *
                 * @see peekByte() for peeking an unsigned byte
                 */
                virtual int8_t peekSignedByte() const = 0;
            };
        }
    }
} // bio

#endif // BIO_ISIMPLEPEEKABLE_H