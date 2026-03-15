/** @file IAccessible.h
 *
 * @author DexrnZacAttack
 * @date 3/13/26
 *
 * @device zPc-i2
 */
#ifndef BIO_IACCESSIBLE_H
#define BIO_IACCESSIBLE_H
#include <cstdint>

namespace bio {
    namespace io {
        namespace interface {
            template <typename T> class IAccessible {
              public:
                virtual ~IAccessible() = default;

                virtual T &operator[](std::size_t p) = 0;
                virtual const T &operator[](std::size_t p) const = 0;

                virtual T &operator*() = 0;
                virtual const T &operator*() const = 0;

                virtual T *operator->() = 0;
                virtual const T *operator->() const = 0;
            };
        } // namespace interface
    } // namespace io
} // namespace bio

#endif // BIO_IACCESSIBLE_H