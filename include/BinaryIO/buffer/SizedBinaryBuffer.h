//
// Created by DexrnZacAttack on 3/5/26 using zPc-i2.
//
#ifndef BIO_SIZEDBINARYBUFFER_H
#define BIO_SIZEDBINARYBUFFER_H
#include "BinaryIO/buffer/BinaryBuffer.h"

namespace bio::buffer {
    /** Sized reader & writer for a byte array */
    class BIO_API SizedBinaryBuffer : public BinaryBuffer {
    public:
        /** Creates a SizedBinaryBuffer with the input ptr as buffer */
        explicit SizedBinaryBuffer(uint8_t *input, size_t size);
        /** Creates a SizedBinaryBuffer with a new array as buffer */
        explicit SizedBinaryBuffer(size_t size);
        //cant impl vector constructor because vector is dynamic

        /** Creates a SizedBinaryBuffer with the given std::array as buffer */
        template <std::size_t Size>
        explicit SizedBinaryBuffer(std::array<uint8_t, Size> &input);

#if __cplusplus >= CPP20
        /** Creates a SizedBinaryBuffer with the given std::span as buffer */
        explicit SizedBinaryBuffer(std::span<uint8_t> &input);

        /** Creates a SizedBinaryBuffer with the given range as buffer */
        template<std::ranges::contiguous_range R>
        requires (!std::is_const_v<std::ranges::range_value_t<R>>)
        explicit SizedBinaryBuffer(R& range);
#endif

        /** Returns the correct pointer based on the specified origin */
        const uint8_t *ptrForOrigin(util::Origin origin) const override;

        /** Returns the correct pointer based on the specified origin */
        uint8_t *ptrForOrigin(util::Origin origin) override;

        /** Returns the size of the buffer */
        size_t size() const;

        /** Returns a pointer to the end of the buffer */
        uint8_t *end();
        /** Returns a pointer to the end of the buffer */
        const uint8_t *end() const;

        /** Returns true if the next byte is out-of-bounds */
        bool eof() const;

    private:
        uint8_t * const m_endPtr; /**< Pointer to the end of the buffer */
    };

#include "SizedBinaryBuffer.tpp"
}

#endif // BIO_SIZEDBINARYBUFFER_H