//
// Created by DexrnZacAttack on 3/5/26 using zPc-i2.
//
#ifndef BIO_BINARYBUFFER_TPP
#define BIO_BINARYBUFFER_TPP

template <size_t Size>
BinaryBuffer::BinaryBuffer(std::array<uint8_t, Size> &input) : BinaryBuffer(input.data()) {}

#if __cplusplus >= CPP20
    template <std::ranges::contiguous_range R>
    requires (!std::is_const_v<std::ranges::range_value_t<R>>)
    BinaryBuffer::BinaryBuffer(R &range) : BinaryBuffer(std::ranges::data(range)) {}
#endif

template <typename T> T BinaryBuffer::read(const util::ByteOrder endian) {
    if (endian == bio::util::ByteOrder::LITTLE) return readLE<T>();

    return this->readBE<T>();
}

template <typename T> T BinaryBuffer::peek(const util::ByteOrder endian, const size_t offset, const util::Origin origin) const {
    if (endian == bio::util::ByteOrder::LITTLE) return this->peekLE<T>(offset, origin);

    return this->peekBE<T>(offset, origin);
}

template <typename T> T BinaryBuffer::readLE() {
    const T v = util::ByteOrderUtil::little2sys(*reinterpret_cast<const T *>(this->m_positionPtr));
    this->m_positionPtr += sizeof(T);
    return v;
}

template <typename T> T BinaryBuffer::peekLE(const size_t offset, const util::Origin origin) const {
    const T v = util::ByteOrderUtil::little2sys(*reinterpret_cast<const T *>(this->ptrForOrigin(origin) + offset));
    return v;
}

template <typename T> T BinaryBuffer::readBE() {
    const T v = util::ByteOrderUtil::big2sys(*reinterpret_cast<const T *>(this->m_positionPtr));
    this->m_positionPtr += sizeof(T);
    return v;
}

template <typename T> T BinaryBuffer::peekBE(const size_t offset, const util::Origin origin) const {
    const T v = util::ByteOrderUtil::big2sys(*reinterpret_cast<const T *>(this->ptrForOrigin(origin) + offset));
    return v;
}

#endif // BIO_BINARYBUFFER_TPP