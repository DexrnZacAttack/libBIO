//
// Created by DexrnZacAttack on 3/6/26 using zPc-i2.
//
#ifndef BIO_BINARYOUTPUTSTREAM_TPP
#define BIO_BINARYOUTPUTSTREAM_TPP

template<typename T>
void BinaryOutputStream::write(const T v, const util::ByteOrder endian) {
    if (endian == util::ByteOrder::LITTLE) {
        this->writeLE(v);
    } else {
        this->writeBE(v);
    }
}

template <typename T>
void BinaryOutputStream::write(const T v) {
    BIO_IF_CONSTEXPR (util::ByteOrder::NATIVE == util::ByteOrder::LITTLE) {
        this->writeLE(v);
    } else {
        this->writeBE(v);
    }
}

template<typename T>
void BinaryOutputStream::writeLE(const T v) {
    T c = util::ByteOrderUtil::little2sys(v);
    m_stream.write(reinterpret_cast<char *>(&c), sizeof(v));
}

template<typename T>
void BinaryOutputStream::writeBE(const T v) {
    T c = util::ByteOrderUtil::big2sys(v);
    m_stream.write(reinterpret_cast<char *>(&c), sizeof(c));
}

template <typename CharT>
void BinaryOutputStream::writeString(
    const platform::ReadableString<CharT> &input, util::ByteOrder byteOrder,
    util::string::StringLengthEncoding lengthEncoding) {
    if (lengthEncoding == util::string::StringLengthEncoding::LENGTH_PREFIX) {
        this->write<uint16_t>(input.size(), byteOrder);
    }

    for (size_t i = 0; i < input.size(); i++) {
        this->write<CharT>(input[i], byteOrder);
    }

    if (lengthEncoding == util::string::StringLengthEncoding::NULL_TERMINATE) {
        this->write<CharT>(0, byteOrder);
    }
}

#endif // BIO_BINARYOUTPUTSTREAM_TPP