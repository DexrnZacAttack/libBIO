/** @file ICanSerialize.h
 *
 * @author DexrnZacAttack
 * @date 3/13/26
 *
 * @device zPc-i2
 */
#ifndef BIO_ICANSERIALIZE_H
#define BIO_ICANSERIALIZE_H
#include <type_traits>

namespace bio {
    namespace io {
        namespace interface {
            /** Hacky interface, since I have to instantiate each serialize method in each class that implements IWritable,
             * ISeekable
             *
             * Once implemented, you can directly call
             * @code
             * bio::buffer::BinaryBuffer buffer(64);
             *
             * buffer.serialize<MySerializable>(options);
             * @endcode
             *
             * instead of
             *
             * @code
             * bio::buffer::BinaryBuffer buffer(64);
             *
             * MySerializable::serialize(buffer, options);
             * @endcode
             */
            class ICanSerialize {
                //clang-format off
#define IMPLEMENT_SERIALIZABLE()                                                                                                 \
                template <typename Serializable, std::enable_if_t<!std::is_void<typename Serializable::Options>::value, int> = 0>            \
                void serialize(const typename Serializable::Type &value, const typename Serializable::Options &options) {                    \
                    return Serializable::serialize(value, *this, options);                                                                   \
                }                                                                                                                            \
                                                                                                                                             \
                template <typename Serializable, std::enable_if_t<std::is_void<typename Serializable::Options>::value, int> = 0>             \
                void serialize(const typename Serializable::Type &value) {                                                                   \
                    return Serializable::serialize(value, *this);                                                                            \
                }
                //clang-format on

                template <typename Serializable, std::enable_if_t<!std::is_void<typename Serializable::Options>::value, int> = 0>
                void serializable(const typename Serializable::Type &value, const typename Serializable::Options &options);

                template <typename Serializable, std::enable_if_t<std::is_void<typename Serializable::Options>::value, int> = 0>
                void serializable(const typename Serializable::Type &value);
            };
        } // namespace interface
    } // namespace io
} // namespace bio

#endif // BIO_ICANSERIALIZE_H