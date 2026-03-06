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

#endif // BIO_BINARYINPUTSTREAM_TPP