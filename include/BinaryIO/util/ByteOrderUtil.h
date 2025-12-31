//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_BYTEORDERUTIL_H
#define BIO_BYTEORDERUTIL_H
#include <cstdint>
#include <stddef.h>
#include <type_traits>
#include <cstring>

namespace bio::util {
    class ByteOrderUtil {
    public:
        ByteOrderUtil() = delete;

        template <typename T>
        static constexpr T swapOrderInternal(const T input) {
            uint8_t resultBytes[sizeof(T)];
            const uint8_t *ib = reinterpret_cast<const uint8_t *>(&input);
            uint8_t *r = resultBytes + (sizeof(T) - 1);

            for (size_t i = 0; i < sizeof(T); ++i) {
                *r-- = *ib++;
            }

            T result;
            memcpy(&result, resultBytes, sizeof(T));
            return result;
        }

        // this is a mess but theoretically will actually use the byteswap
        // instruction
        template <typename T>
        static constexpr T swapOrder(const T input) {
            if constexpr (std::is_integral_v<T>) {
                if constexpr (sizeof(T) == 2) {
#if defined(__clang__) || defined(__GNUC__)
                    return static_cast<T>(
                        __builtin_bswap16(static_cast<uint16_t>(input)));
#elif defined(_MSC_VER)
                    return static_cast<T>(
                        _byteswap_ushort(static_cast<unsigned short>(input)));
#else
                    return swapOrderInternal(input);
#endif
                } else if constexpr (sizeof(T) == 4) {
#if defined(__clang__) || defined(__GNUC__)
                    return static_cast<T>(
                        __builtin_bswap32(static_cast<uint32_t>(input)));
#elif defined(_MSC_VER)
                    return static_cast<T>(
                        _byteswap_ulong(static_cast<unsigned long>(input)));
#else
                    return swapOrderInternal(input);
#endif
                } else if constexpr (sizeof(T) == 8) {
#if defined(__clang__) || defined(__GNUC__)
                    return static_cast<T>(
                        __builtin_bswap64(static_cast<uint64_t>(input)));
#elif defined(_MSC_VER)
                    return static_cast<T>(
                        _byteswap_uint64(static_cast<unsigned __int64>(input)));
#else
                    return swapOrderInternal(input);
#endif
                } else {
                    return swapOrderInternal(input);
                }
            } else {
                return swapOrderInternal(input);
            }
        }

        template <typename T>
        static constexpr T big2sys(const T a) {
#ifdef BR_BIG_ENDIAN
            return a;
#else
            return swapOrder(a);
#endif
        }

        template <typename T>
        static constexpr T little2sys(const T a) { // also is working as sys2little
#ifdef BR_BIG_ENDIAN
            return swapOrder(a);
#else
            return a;
#endif
        }
    };
}

#endif //BIO_BYTEORDERUTIL_H