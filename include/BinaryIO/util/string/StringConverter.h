//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#ifndef BIO_STRINGCONVERTER_H
#define BIO_STRINGCONVERTER_H
#include <string>

#include "BinaryIO/Library.h"

namespace bio::util::string {
    class BIO_API StringConverter {
    public:
        StringConverter() = delete;

        // TODO we need to make these not suck, and probably templated too
        static std::wstring u16stringToWstring(const std::u16string &str);
        static std::u16string wstringToU16string(const std::wstring &str);
        static std::wstring u32stringToWstring(const std::u32string &str);
        static std::string u16stringToString(const std::u16string &str);
        static std::u16string stringToU16String(const std::string &str);
        static std::string wstringToString(const std::wstring &str);
        static std::wstring stringToWString(const std::string &str);
    };
}

#endif //BIO_STRINGCONVERTER_H
