//
// Created by DexrnZacAttack on 3/6/26 using zPc-i2.
//
#ifndef BIO_BINARYOUTPUTSTREAM_TPP
#define BIO_BINARYOUTPUTSTREAM_TPP

template<typename T>
void BinaryOutputStream::write(const T v, const util::ByteOrder endian) {
    if (endian == util::ByteOrder::LITTLE) this->writeLE(v);
    else this->writeBE(v);
}

template<typename T>
void BinaryOutputStream::writeLE(const T v) {
    T c = util::ByteOrderUtil::little2sys(v);
    m_stream.write(reinterpret_cast<char *>(&c), sizeof(v));
}

template<typename T>
void BinaryOutputStream::writeBE(const T v) {
    T c = util::ByteOrderUtil::big2sys(v);
    m_stream.write(reinterpret_cast<char *>(&c), sizeof(v));
}

#endif // BIO_BINARYOUTPUTSTREAM_TPP