//
// Created by DexrnZacAttack on 3/5/26 using zPc-i2.
//
#ifndef BIO_BINARYBUFFER_TPP
#define BIO_BINARYBUFFER_TPP

template <size_t Size> BinaryBuffer::BinaryBuffer(std::array<uint8_t, Size> &input) : BinaryBuffer(input.data()) {}

#if __cplusplus >= CPP20
template <std::ranges::contiguous_range R>
    requires(!std::is_const_v<std::ranges::range_value_t<R>>)
BinaryBuffer::BinaryBuffer(R &range) : BinaryBuffer(std::ranges::data(range)) {}
#endif

template <typename T> T BinaryBuffer::read(const util::ByteOrder endian) {
    if (endian == bio::util::ByteOrder::LITTLE)
        return readLE<T>();

    return this->readBE<T>();
}

template <typename T> T BinaryBuffer::read() {
    BIO_IF_CONSTEXPR(bio::util::ByteOrder::NATIVE == bio::util::ByteOrder::LITTLE)
    return readLE<T>();

    return this->readBE<T>();
}

template <typename T> T BinaryBuffer::peek(const util::ByteOrder endian, const size_t offset, const util::Origin origin) const {
    if (endian == bio::util::ByteOrder::LITTLE)
        return this->peekLE<T>(offset, origin);

    return this->peekBE<T>(offset, origin);
}

template <typename T> T BinaryBuffer::peek(const size_t offset, const util::Origin origin) const {
    BIO_IF_CONSTEXPR(bio::util::ByteOrder::NATIVE == bio::util::ByteOrder::LITTLE)
    return this->peekLE<T>(offset, origin);

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

template <typename T> void BinaryBuffer::write(const T v, const util::ByteOrder endian) {
    if (endian == util::ByteOrder::LITTLE) {
        this->writeLE<T>(v);
    } else {
        this->writeBE<T>(v);
    }
}

template <typename T> void BinaryBuffer::write(const T v) {
    BIO_IF_CONSTEXPR(util::ByteOrder::NATIVE == util::ByteOrder::LITTLE) { this->writeLE<T>(v); }
    else {
        this->writeBE<T>(v);
    }
}

template <typename T> void BinaryBuffer::writeLE(const T v) {
    *reinterpret_cast<T *>(this->m_positionPtr) = util::ByteOrderUtil::little2sys(v);
    this->m_positionPtr += sizeof(T);
}

template <typename T> void BinaryBuffer::writeBE(const T v) {
    *reinterpret_cast<T *>(this->m_positionPtr) = util::ByteOrderUtil::big2sys(v);
    this->m_positionPtr += sizeof(T);
}

template <typename CharT, typename>
std::basic_string<CharT> BinaryBuffer::readString(size_t length, const util::ByteOrder endian) {
    if (endian == util::ByteOrder::NATIVE) {
        CharT *p = reinterpret_cast<CharT *>(this->m_positionPtr);

        std::basic_string<CharT> s(p, p + length);
        this->m_positionPtr += length * sizeof(CharT);

        return s;
    }

    std::basic_string<CharT> s(length, 0);
    for (size_t i = 0; i < length; i++) {
        s[i] = this->read<CharT>(endian);
    }

    return s;
}

template <typename CharT, typename> std::basic_string<CharT> BinaryBuffer::readString(const size_t length) {
    CharT *p = reinterpret_cast<CharT *>(this->m_positionPtr);

    std::basic_string<CharT> s(p, p + length);
    this->m_positionPtr += (length * sizeof(CharT));

    return s;
}

template <typename CharT, typename>
std::basic_string<CharT> BinaryBuffer::readStringNullTerminated(const util::ByteOrder endian) {
    const size_t len = std::char_traits<CharT>::length(reinterpret_cast<CharT *>(this->m_positionPtr));
    std::basic_string<CharT> str = this->readString<CharT>(len, endian);

    // null terminator
    this->m_positionPtr += 1 * sizeof(CharT);

    return str;
}

template <typename CharT, typename> std::basic_string<CharT> BinaryBuffer::readStringNullTerminated() {
    CharT *p = reinterpret_cast<CharT *>(this->m_positionPtr);

    const size_t len = std::char_traits<CharT>::length(p);

    std::basic_string<CharT> str = std::basic_string<CharT>(p, p + len);
    this->m_positionPtr += len * sizeof(CharT);
    this->m_positionPtr += 1 * sizeof(CharT); // null terminator

    return str;
}

template <typename CharT>
void BinaryBuffer::writeString(const platform::ReadableString<CharT> &input, const util::ByteOrder byteOrder,
                               const util::string::StringLengthEncoding lengthEncoding) {
    if (lengthEncoding == util::string::StringLengthEncoding::LENGTH_PREFIX) {
        this->write<uint16_t>(input.size(), byteOrder);
    }

    BIO_IF_CONSTEXPR(sizeof(CharT) == 1) {
        const size_t byteLen = input.size() * sizeof(CharT);

        memcpy(this->m_positionPtr, reinterpret_cast<const uint8_t *>(input.data()), byteLen);
        this->m_positionPtr += byteLen;
    }
    else {
        for (size_t i = 0; i < input.size(); i++) {
            this->write<CharT>(input[i], byteOrder);
        }
    }

    if (lengthEncoding == util::string::StringLengthEncoding::NULL_TERMINATE) {
        this->write<CharT>(0, byteOrder);
    }
}

#endif // BIO_BINARYBUFFER_TPP