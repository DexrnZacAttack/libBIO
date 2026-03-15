/** @file Serializable.h
 *
 * @author DexrnZacAttack
 * @date 3/13/26
 * 
 * @device zPc-i2
 */
#ifndef BIO_SERIALIZABLE_H
#define BIO_SERIALIZABLE_H

#include "interface/IPeekable.h"
#include "interface/ISeekable.h"

#include <concepts>
#include <concepts>
#include <memory>

namespace bio {
    namespace io {
        namespace interface {
            class IWritable;
            class IReadable;
        }

#if __cplusplus >= CPP20
        template <typename T, typename... Bases>
        concept DerivedFromAll = (std::is_base_of_v<Bases, T> && ...);

        /** Describes a buffer/stream which can be read from, and is seekable */
        template <typename T>
        concept ReadableBufferLike = DerivedFromAll<T, bio::io::interface::IReadable, bio::io::interface::ISeekable>;

        /** Describes a buffer/stream which can be written to, and is seekable */
        template <typename T>
        concept WritableBufferLike = DerivedFromAll<T, bio::io::interface::IWritable, bio::io::interface::ISeekable>;
#endif

        template <typename T, typename O>
        class Serializable {
        public:
            using Options = O;
            using Type = T;

#if __cplusplus >= CPP20
            /** Serializes the value into the given IWritable */
            static void serialize(const Type &value, WritableBufferLike auto &writable, const Options &options);
#else
            /** Serializes the value into the given IWritable */
            static void serialize(const Type &value, interface::IWritable &writable, const Options &options);
#endif
        };

        template <typename T, typename O>
        class Deserializable {
        public:
            using Options = O;
            using Type = T;

#if __cplusplus >= CPP20
            /** Deserializes the value from the given IReadable */
            static std::unique_ptr<Type> deserialize(ReadableBufferLike auto &readable, const Options &options);
#else
            /** Deserializes the value from the given IReadable */
            static std::unique_ptr<Type> deserialize(interface::IReadable &readable, const Options &options);
#endif
        };
    } // io
} // bio

#endif // BIO_SERIALIZABLE_H