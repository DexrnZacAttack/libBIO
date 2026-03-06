//
// Created by DexrnZacAttack on 3/5/26 using zPc-i2.
//
#ifndef BIO_IBUFFER_H
#define BIO_IBUFFER_H

#include "BinaryIO/Platform.h"

#if __cplusplus >= CPP20
#include <span>
#endif

namespace bio::io {
    /** Interface to provide memory buffer utility methods */
    class IBuffer {
    public:
        virtual ~IBuffer() = default;

#if __cplusplus >= CPP20
        /** Returns a view over the data of given size */
        virtual std::span<uint8_t> getView(size_t sz) = 0;

        /** Returns a view over the data of given size */
        virtual std::span<const uint8_t> getView(size_t sz) const = 0;
#endif
    };
}

#endif // BIO_IBUFFER_H