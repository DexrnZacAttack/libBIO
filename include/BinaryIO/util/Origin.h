//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_ORIGIN_H
#define BIO_ORIGIN_H

#include "BinaryIO/Library.h"
#include "BinaryIO/Platform.h"

#include <algorithm>

namespace bio {
    namespace util {
        enum class BIO_API EOrigin : int {
            START, /**< Origin pointer */
            CURRENT_POSITION, /**< Current position */
            END, /**< End position */
            INVALID_VALUE /**< Invalid value, this is not meant to be used by the user. */
        };

        /** Pointer origin.
         *
         * @note It's a class so the library user may add on their own origin types and handle them explicitly in their implementations of IPeekable
         */
        class BIO_API Origin {
        public:
            constexpr Origin(const EOrigin origin) : m_origin(
                static_cast<int>(origin)) {
            }

            constexpr explicit Origin(const int origin) : m_origin(origin) {
            }

            explicit constexpr operator int() const {
                return this->m_origin;
            }

            constexpr operator EOrigin() const {
                //cant define more inside our enum so we'll guard it
                if (this->m_origin > static_cast<int>(EOrigin::END) || this->m_origin < static_cast<int>(EOrigin::START))
                    return EOrigin::INVALID_VALUE;

                return static_cast<EOrigin>(bio::platform::clamp(
                    this->m_origin,
                    static_cast<int>(EOrigin::START),
                    static_cast<int>(EOrigin::END)
                    ));
            }

            constexpr bool operator==(const Origin &rhs) const {
                return this->m_origin == rhs.m_origin;
            }

            const int m_origin;
        };
    }
}

#endif //BIO_ORIGIN_H