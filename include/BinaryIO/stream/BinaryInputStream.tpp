//
// Created by DexrnZacAttack on 3/6/26 using zPc-i2.
//
#ifndef BIO_BINARYINPUTSTREAM_TPP
#define BIO_BINARYINPUTSTREAM_TPP

template<typename T>
T BinaryInputStream::read(const util::ByteOrder endian) {
    if (endian == bio::util::ByteOrder::LITTLE) return readLE<T>();

    return readBE<T>();
}

template <typename T>
T BinaryInputStream::read() {
    BIO_IF_CONSTEXPR (bio::util::ByteOrder::NATIVE == bio::util::ByteOrder::LITTLE)
        return readLE<T>();

    return readBE<T>();
}

template<typename T>
T BinaryInputStream::readLE() {
    T p;
    m_stream.read(reinterpret_cast<char *>(&p), sizeof(p));

    return util::ByteOrderUtil::little2sys(p);
}

template<typename T>
T BinaryInputStream::readBE() {
    T p;
    m_stream.read(reinterpret_cast<char *>(&p), sizeof(p));

    return util::ByteOrderUtil::big2sys(p);
}

template <typename CharT, typename>
std::basic_string<CharT> BinaryInputStream::readString(size_t length, const util::ByteOrder endian) {
    std::basic_string<CharT> s(length, 0);
    for (size_t i = 0; i < length; i++) {
        s[i] = this->read<CharT>(endian);
    }

    return s;
}

template <typename CharT, typename>
std::basic_string<CharT> BinaryInputStream::readString(const size_t length) {
    const size_t byteLen = length * sizeof(CharT);
    CharT *chars = reinterpret_cast<CharT *>(this->readOfSize(byteLen));

    return std::basic_string<CharT>(chars, chars + byteLen);
}

template <typename CharT>
std::basic_string<CharT> BinaryInputStream::readStringWithLength(util::ByteOrder endian, util::string::StringLengthEncoding lengthEncoding) {
    std::basic_string<CharT> str;

    switch (lengthEncoding) {
    case util::string::StringLengthEncoding::NULL_TERMINATE: {
        CharT c;
        while ((c = this->read<CharT>(endian)) != 0) {
            str.push_back(c);
        }
        break;
    }
    case util::string::StringLengthEncoding::LENGTH_PREFIX: {
        const uint16_t len = this->read<uint16_t>(endian);

        for (int i = 0; i < len; i++) {
            str.push_back(this->read<CharT>(endian));
        }
        break;
    }
    case util::string::StringLengthEncoding::NONE:
        //if user puts in NONE, how are we supposed to get length??????
        throw std::invalid_argument("StringLengthEncoding::NONE is not valid here, please use readString instead and provide your own length value.");
    }

    return str;
}

template <typename CharT, typename> std::basic_string<CharT> BinaryInputStream::readCharStringNullTerminated() {
    return this->readStringWithLength<CharT>(util::ByteOrder::NATIVE, util::string::StringLengthEncoding::NULL_TERMINATE);
}

#endif // BIO_BINARYINPUTSTREAM_TPP