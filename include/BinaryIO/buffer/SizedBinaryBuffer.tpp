//
// Created by DexrnZacAttack on 3/5/26 using zPc-i2.
//
#ifndef BIO_SIZEDBINARYBUFFER_TPP
#define BIO_SIZEDBINARYBUFFER_TPP

template <size_t Size>
SizedBinaryBuffer::SizedBinaryBuffer(std::array<uint8_t, Size> &input) : SizedBinaryBuffer(input.data(), input.size()) {
}

#if __cplusplus >= CPP20
    template <std::ranges::contiguous_range R>
    requires (!std::is_const_v<std::ranges::range_value_t<R>>)
    SizedBinaryBuffer::SizedBinaryBuffer(R &range) : SizedBinaryBuffer(std::ranges::data(range), std::ranges::size(range)) {}
#endif

#endif // BIO_BINARYBUFFER_TPP