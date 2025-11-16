//
// Created by DexrnZacAttack on 11/15/25 using zPc-i2.
//
#include "BinaryIO/util/string/StringConverter.h"

#include <codecvt>
#include <locale>

namespace bio::util::string {
    std::wstring StringConverter::u16stringToWstring(const std::u16string &str) {
#if WCHAR_MAX == 0xffff
        return std::wstring(str.begin(), str.end());
#else
        std::wstring result;
        result.reserve(str.size());

        for (const char16_t c: str) {
            result.push_back(static_cast<wchar_t>(c));
        }
        return result;
#endif
    }

    std::u16string StringConverter::wstringToU16string(const std::wstring &str) {
#if WCHAR_MAX == 0xffff
        return std::u16string(str.begin(), str.end());
#else
        std::u16string result;
        result.reserve(str.size());

        for (const wchar_t c: str) {
            result.push_back(static_cast<char16_t>(c));
        }
        return result;
#endif
    }

    std::wstring StringConverter::u32stringToWstring(const std::u32string &str) {
#if WCHAR_MAX == 0x7fffffff
        return {str.begin(), str.end()};
#else
        // LOSSY LOSSY LOSSY LOSSY LOSSY AAAAAAAAAAAAA
        std::wstring result;
        result.reserve(str.size());

        for (char32_t c: str) {
            result.push_back(static_cast<wchar_t>(c));
        }
        return result;
#endif
    }

    std::string StringConverter::u16stringToString(const std::u16string &str) {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>
                convert;
        return convert.to_bytes(str);
    }

    std::u16string StringConverter::stringToU16String(const std::string &str) {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>
                convert;
        return convert.from_bytes(str);
    }

    std::string StringConverter::wstringToString(const std::wstring &str) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t> > convert;
        return convert.to_bytes(str);
    }

    std::wstring StringConverter::stringToWString(const std::string &str) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
        return convert.from_bytes(str);
    }
}
