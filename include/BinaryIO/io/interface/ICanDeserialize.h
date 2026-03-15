/** @file ICanDeserialize.h
 *
 * @author DexrnZacAttack
 * @date 3/13/26
 *
 * @device zPc-i2
 */
#ifndef BIO_ICANDESERIALIZE_H
#define BIO_ICANDESERIALIZE_H
#include <memory>
#include <type_traits>

namespace bio {
    namespace io {
        namespace interface {
            /** Hacky interface, since I have to instantiate each deserialize method in each class that implements IReadable,
             * ISeekable
             *
             * Once implemented, you can directly call
             * @code
             * bio::buffer::BinaryBuffer buffer(64);
             * buffer.deserialize<MyDeserializable>(options);
             * @endcode
             *
             * instead of
             *
             * @code
             * bio::buffer::BinaryBuffer buffer(64);
             * MyDeserializable::deserialize(buffer, options);
             * @endcode
             */
            class ICanDeserialize {
                //clang-format off
#define IMPLEMENT_DESERIALIZABLE()                                                                                               \
                template <typename Deserializable, std::enable_if_t<!std::is_void<typename Deserializable::Options>::value, int> = 0>        \
                std::unique_ptr<typename Deserializable::Type> deserialize(const typename Deserializable::Options &options) {                \
                    return Deserializable::deserialize(*this, options);                                                                      \
                }                                                                                                                            \
                                                                                                                                             \
                template <typename Deserializable, std::enable_if_t<std::is_void<typename Deserializable::Options>::value, int> = 0>         \
                std::unique_ptr<typename Deserializable::Type> deserialize() {                                                               \
                    return Deserializable::deserialize(*this);                                                                               \
                }
                //clang-format on

                template <typename Deserializable,
                          std::enable_if_t<!std::is_void<typename Deserializable::Options>::value, int> = 0>
                std::unique_ptr<typename Deserializable::Type> deserialize(const typename Deserializable::Options &options);

                template <typename Deserializable,
                          std::enable_if_t<std::is_void<typename Deserializable::Options>::value, int> = 0>
                std::unique_ptr<typename Deserializable::Type> deserialize();
            };
        } // namespace interface
    } // namespace io
} // namespace bio

#endif // BIO_ICANDESERIALIZE_H