//
// Created by DexrnZacAttack on 3/5/26 using zPc-i2.
//
#ifndef BIO_PLATFORM_H
#define BIO_PLATFORM_H

#include <algorithm>

#define CPP23 202302L
#define CPP20 202002L
#define CPP17 201703L
#define CPP14 201402L
#define CPP11 201103L

namespace bio {
    namespace platform {
#if __cplusplus < CPP17 && !defined(BIO_ALLOW_CPP17_EXTENSIONS) //if below cpp17 and extensions haven't been explicitly allowed
//set to if
#   define BIO_IF_CONSTEXPR if
#else
#   define BIO_IF_CONSTEXPR if constexpr
#endif

        template <typename T>
        constexpr size_t clamp(const T value, const T min, const T max) {
#if __cplusplus < CPP17
            return std::max(min, std::min(value, max));
#else
            return std::clamp(value, min, max);
#endif
        }
    }
}

#endif // BIO_PLATFORM_H