//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_BYTEORDERUTIL_H
#define BIO_BYTEORDERUTIL_H
#include <cstdint>
#include <stddef.h>
#include <type_traits>
#include <cstring>
#include "BinaryIO/Platform.h" // NOLINT (needed for BIO_IF_CONSTEXPR)

#include <iostream>

#if __cplusplus >= CPP23
#include <bit>
#endif

namespace bio {
    namespace util {
#if defined(_MSC_VER)
#define byteswap16 _byteswap_ushort
#define byteswap32 _byteswap_ulong
#define byteswap64 _byteswap_uint64
#elif defined(__GNUC__)
#define byteswap16 __builtin_bswap16
#define byteswap32 __builtin_bswap32
#define byteswap64 __builtin_bswap64
#else
#define byteswap16 basicSwapOrder<uint16_t>
#define byteswap32 basicSwapOrder<uint32_t>
#define byteswap64 basicSwapOrder<uint64_t>
#endif

        class BIO_API ByteOrderUtil {
        public:
            ByteOrderUtil() = delete;

            template <typename T, const std::size_t SZ>
            static constexpr T sizedBasicSwapOrder(T input) {
                std::remove_reference_t<T> in = input;

                BIO_IF_CONSTEXPR (SZ == 1)
                    return in;

                //evil
                std::reverse(reinterpret_cast<uint8_t *>(&in), reinterpret_cast<uint8_t *>(&in) + SZ);

                return in;
            }

            template <typename T>
            static constexpr T basicSwapOrder(T input) {
                return sizedBasicSwapOrder<T, sizeof(T)>(input);
            }

            template <typename T>
            static constexpr T swapOrder(T input) {
                BIO_IF_CONSTEXPR (sizeof(T) == 1) {
                    return input;
                }

                BIO_IF_CONSTEXPR (std::is_integral<T>::value) {
                    // cpp23
// #if __cplusplus >= CPP23
//                     return std::byteswap(input);
// #else

                    //otherwise, directly call compiler intrinsics
                    BIO_IF_CONSTEXPR (sizeof(T) == 2) {
                        return static_cast<T>(byteswap16(static_cast<uint16_t>(input)));
                    } else BIO_IF_CONSTEXPR (sizeof(T) == 4) {
                        return static_cast<T>(byteswap32(static_cast<uint32_t>(input)));
                    } else BIO_IF_CONSTEXPR (sizeof(T) == 8) {
                        return static_cast<T>(byteswap64(static_cast<uint64_t>(input)));
                    }
// #endif
                }

                // otherwise, manual impl
                return basicSwapOrder(input);
            }

            template <typename T>
            static constexpr T big2sys(const T a) {
#ifdef BIO_BIG_ENDIAN
                return a;
#else
                return swapOrder(a);
#endif
            }

            template <typename T>
            static constexpr T little2sys(const T a) { // also is working as sys2little
#ifdef BIO_BIG_ENDIAN
                return swapOrder(a);
#else
                return a;
#endif
            }
        };
    }
}

#endif //BIO_BYTEORDERUTIL_H