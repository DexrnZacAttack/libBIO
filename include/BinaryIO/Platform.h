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
#define CPP98 199711L

#if __cplusplus >= CPP23
#define BIO_CPP_VERSION 23
#elif __cplusplus >= CPP20
#define BIO_CPP_VERSION 20
#elif __cplusplus >= CPP17
#define BIO_CPP_VERSION 17
#elif __cplusplus >= CPP14
#define BIO_CPP_VERSION 14
#elif __cplusplus >= CPP11
#define BIO_CPP_VERSION 11
#elif __cplusplus >= CPP98
#define BIO_CPP_VERSION 98
#else
//unk
#define BIO_CPP_VERSION 0xDEAD
#endif

#if __cplusplus >= CPP17
#include <string_view>
#else
#include <string>
#endif


namespace bio {
    namespace platform {
#if __cplusplus >= CPP17
        template <typename CharT>
        using ReadableString = std::basic_string_view<CharT>;
#else
        template <typename CharT>
        using ReadableString = std::basic_string<CharT>;
#endif

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