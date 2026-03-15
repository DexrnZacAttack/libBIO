//
// Created by (Person who prefers not to be named) and DexrnZacAttack on
// 20/12/2024.
//

#ifndef BINARYIO_H
#define BINARYIO_H

#include <cstdint>
#include <string>
#include <vector>

#include "BinaryIO/Library.h"
#include "BinaryIO/container/FixedArray.h"
#include "BinaryIO/io/interface/IBuffer.h"
#include "BinaryIO/io/interface/ICanDeserialize.h"
#include "BinaryIO/io/interface/ICanSerialize.h"
#include "BinaryIO/io/interface/IPeekable.h"
#include "BinaryIO/io/interface/IReadable.h"
#include "BinaryIO/io/interface/ISeekable.h"
#include "BinaryIO/io/interface/IWritable.h"
#include "BinaryIO/util/ByteOrder.h"
#include "BinaryIO/util/ByteOrderUtil.h"
#include "BinaryIO/util/Origin.h"

namespace bio {
    namespace buffer {
        // TODO in the future we can actually make this templated, will work nicely.
        /** Unsized reader & writer for a byte array
         *
         * @sa @ref binarybuffer "The documentation page for BinaryBuffer"
         */
        class BIO_API BinaryBuffer : public io::interface::IReadable,
                                     public io::interface::IPeekable,
                                     public io::interface::IWritable,
                                     public io::interface::ISeekable,
                                     public io::interface::IBuffer,
                                     public io::interface::ICanDeserialize,
                                     public io::interface::ICanSerialize {
          public:
            /** Creates a BinaryBuffer with the given input ptr as buffer */
            explicit BinaryBuffer(uint8_t *input);

            /** Creates a BinaryBuffer with a new array as buffer */
            explicit BinaryBuffer(size_t size);

            /** Creates a BinaryBuffer with the given input vector's data ptr as buffer */
            explicit BinaryBuffer(std::vector<uint8_t> &input);

            /** Creates a BinaryBuffer with the given input array's data ptr as buffer */
            template <std::size_t Size> explicit BinaryBuffer(std::array<uint8_t, Size> &input);

            /** Creates a BinaryBuffer with the given input array's data ptr as buffer */
            explicit BinaryBuffer(container::FixedArray<uint8_t> &input);

#if __cplusplus >= CPP20
            /** Creates a BinaryBuffer with the given input span's data ptr as buffer */
            explicit BinaryBuffer(std::span<uint8_t> &input);

            /** Creates a BinaryBuffer with the given input range's data ptr as buffer */
            template <std::ranges::contiguous_range R>
                requires(!std::is_const_v<std::ranges::range_value_t<R>>)
            explicit BinaryBuffer(R &range);
#endif

            ~BinaryBuffer() override;

            void seek(size_t offset) override;

            void seekRelative(size_t offset) override;

            bool canSeek() const override;

            IMPLEMENT_DESERIALIZABLE()
            IMPLEMENT_SERIALIZABLE()

            // reading
            /** Reads a value the size of the given type using the given endian/byte
             * order
             *
             * @param endian The byte order to read as
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             * @see readLE() for reading a Little Endian value
             */
            template <typename T> T read(const util::ByteOrder endian);

            /** Reads a value the size of the given type using the platform endian/byte
             * order
             *
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             * @see readLE() for reading a Little Endian value
             */
            template <typename T> T read();

            /** Reads a value the size of the given type using the given endian/byte
             * order
             *
             * @note Does not increment the position
             *
             * @param endian The byte order to read as
             * @param offset Offset to peek at (zero for byte at given origin)
             * @param origin Origin to peek from. @ref bio::util::EOrigin::CURRENT_POSITION applies the offset to the current
             * position, while @ref bio::util::EOrigin::START applies the offset to the data origin.
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             * @see readLE() for reading a Little Endian value
             */
            template <typename T>
            T peek(const util::ByteOrder endian, const size_t offset = 0,
                   const util::Origin origin = util::EOrigin::CURRENT_POSITION) const;

            /** Reads a value the size of the given type using the platform endian/byte
             * order
             *
             * @note Does not increment the position
             *
             * @param offset Offset to peek at (zero for byte at given origin)
             * @param origin Origin to peek from. @ref bio::util::EOrigin::CURRENT_POSITION applies the offset to the current
             * position, while @ref bio::util::EOrigin::START applies the offset to the data origin.
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             * @see readLE() for reading a Little Endian value
             */
            template <typename T>
            T peek(const size_t offset = 0, const util::Origin origin = util::EOrigin::CURRENT_POSITION) const;

            /** Reads a value the size of the given type as Little Endian
             *
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             */
            template <typename T> T readLE();

            /** Reads a value the size of the given type as Little Endian
             *
             * @note Does not increment the position
             *
             * @param offset Offset to peek at (zero for byte at given origin)
             * @param origin Origin to peek from. @ref bio::util::EOrigin::CURRENT_POSITION applies the offset to the current
             * position, while @ref bio::util::EOrigin::START applies the offset to the data origin.
             *
             * @returns The value
             *
             * @see readBE() for reading a Big Endian value
             */
            template <typename T>
            T peekLE(const size_t offset = 0, const util::Origin origin = util::EOrigin::CURRENT_POSITION) const;

            /** Reads a value the size of the given type as Big Endian
             *
             * @returns The value
             *
             * @see readLE() for reading a Little Endian value
             */
            template <typename T> T readBE();

            /** Reads a value the size of the given type as Big Endian
             *
             * @note Does not increment the position
             *
             * @param offset Offset to peek at (zero for byte at given origin)
             * @param origin Origin to peek from. @ref bio::util::EOrigin::CURRENT_POSITION applies the offset to the current
             * position, while @ref bio::util::EOrigin::START applies the offset to the data origin.
             *
             * @returns The value
             *
             * @see readLE() for reading a Little Endian value
             */
            template <typename T>
            T peekBE(const size_t offset = 0, const util::Origin origin = util::EOrigin::CURRENT_POSITION) const;

            uint8_t readByte() override;

            uint8_t peekByte(util::Origin origin, size_t offset) const override;

            int8_t readSignedByte() override;

            int8_t peekSignedByte(util::Origin origin, size_t offset) const override;

            uint32_t readUint24(util::ByteOrder endian) override;

            uint32_t peekUint24(bio::util::ByteOrder endian, util::Origin origin, size_t offset) const override;

            int32_t readInt24(util::ByteOrder endian) override;

            int32_t peekInt24(bio::util::ByteOrder endian, util::Origin origin, size_t offset) const override;

            uint8_t *readOfSize(size_t sz) override;

            uint8_t *peekOfSize(size_t sz, util::Origin origin, size_t offset) const override;

            std::vector<uint8_t> readOfSizeVec(size_t sz) override;

            std::vector<uint8_t> peekOfSizeVec(size_t sz, util::Origin origin, size_t offset) const override;

            void readInto(uint8_t *into, size_t sz) override;

            void peekInto(uint8_t *into, size_t sz, util::Origin origin, size_t offset) const override;

            // writing
            /** Writes a value with the given endianness
             *
             * @param v The value to write
             * @param endian The byte order to write that value in
             */
            template <typename T> void write(const T v, const util::ByteOrder endian);

            /** Writes a value with the platform endianness
             *
             * @param v The value to write
             */
            template <typename T> void write(const T v);

            /** Writes a value in Little Endian
             *
             * @param v The value to write
             */
            template <typename T> void writeLE(const T v);

            /** Writes a value in Big Endian
             *
             * @param v The value to write
             */
            template <typename T> void writeBE(const T v);

            void writeByte(uint8_t v) override;

            void writeSignedByte(int8_t v) override;

            void writeUint24(uint32_t v, bio::util::ByteOrder endian) override;

            void writeInt24(int32_t v, bio::util::ByteOrder endian) override;

            void writeBytes(const uint8_t *v, size_t size) override;

            /** Reads a wide string with the given length
             *
             * @returns The string
             */
            template <typename CharT, typename = std::enable_if_t<(sizeof(CharT) > 1)>>
            std::basic_string<CharT> readString(size_t length, util::ByteOrder endian);

            /** Reads a multibyte string with the given length
             *
             * @returns The string
             */
            template <typename CharT, typename = std::enable_if_t<sizeof(CharT) == 1>>
            std::basic_string<CharT> readString(size_t length);

            /** Reads a null terminated wide string
             *
             * @returns The string
             */
            template <typename CharT, typename = std::enable_if_t<(sizeof(CharT) > 1)>>
            std::basic_string<CharT> readStringNullTerminated(util::ByteOrder endian);

            /** Reads a null terminated multibyte string
             *
             * @returns The string
             */
            template <typename CharT, typename = std::enable_if_t<sizeof(CharT) == 1>>
            std::basic_string<CharT> readStringNullTerminated();

            /** Writes a string
             *
             * @param input The input string
             * @param byteOrder The byte order for each char to be written with, if sizeof(CharT) is 1, this will be only used for
             * writing the lengthEncoding
             * @param lengthEncoding The method in which we should encode the length alongside the string
             */
            template <typename CharT>
            void writeString(const platform::ReadableString<CharT> &input, util::ByteOrder byteOrder,
                             util::string::StringLengthEncoding lengthEncoding);

#if __cplusplus >= CPP20
            std::span<uint8_t> getView(size_t sz) override;

            std::span<const uint8_t> getView(size_t sz) const override;
#endif

            /** Returns the correct pointer based on the specified origin
             *
             * Returns nullptr if Origin value is not accepted
             *
             * Does not accept @ref bio::util::EOrigin::END
             */
            virtual uint8_t *ptrForOrigin(util::Origin origin);

            /** Returns the correct pointer based on the specified origin
             *
             * Returns nullptr if Origin value is not accepted
             *
             * Does not accept @ref bio::util::EOrigin::END
             */
            virtual const uint8_t *ptrForOrigin(util::Origin origin) const;

            /** Returns the origin pointer */
            uint8_t *begin();

            /** Returns the position pointer */
            uint8_t *position();

            /** Returns the origin pointer */
            const uint8_t *begin() const;

            /** Returns the position pointer */
            const uint8_t *position() const;

            size_t getOffset() const override;

            /** Returns a byte at the given offset */
            uint8_t &operator[](size_t i);

            /** Returns a byte at the given offset */
            const uint8_t &operator[](size_t i) const;

            ISeekable &operator+=(size_t amount) override;

            ISeekable &operator-=(size_t amount) override;

          protected:
            uint8_t *const m_originPtr; /**< Data origin */
            uint8_t *m_positionPtr = m_originPtr;
            /**< Data pointer, holds where we are in the array */

            bool m_owned = false;
            /**< Whether we own the pointer, used to delete[] the origin pointer on destruction if needed */
        };

#include "BinaryBuffer.tpp"
    } // namespace buffer
} // namespace bio

#endif // BINARYIO_H
