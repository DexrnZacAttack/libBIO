//
// Created by DexrnZacAttack on 3/3/26 using zPc-i2.
//
#ifndef BIO_OUTPUT_H
#define BIO_OUTPUT_H
#include "BinaryIO/Tests/util/Random.h"

namespace bio::tests::util {
    struct Output {
        struct SerializerOptions {
            bio::util::ByteOrder byteOrder;
        };

        using Serializer = bio::io::Serializable<Output, SerializerOptions>;
        using Deserializer = bio::io::Deserializable<Output, SerializerOptions>;

        bool b;
        signed char c;
        unsigned char uc;
        signed short s;
        unsigned short us;
        signed int i;
        unsigned int ui;
        signed long l;
        unsigned long ul;
        signed long long ll;
        unsigned long long ull;

        float f;
        double d;
        // Serializing long double seems to be a bad idea in general
        // long double ld;

        std::string str = "";
        std::u16string str16 = u"";
        std::u32string str32 = U"";

        bool operator==(const Output &rhs) const = default;

        static Output fromRandom() {
            return Output{
                Random::value<bool>(false, true),
                Random::value<signed char>(),
                Random::value<unsigned char>(),
                Random::value<signed short>(),
                Random::value<unsigned short>(),
                Random::value<signed int>(),
                Random::value<unsigned int>(),
                Random::value<signed long>(),
                Random::value<unsigned long>(),
                Random::value<signed long long>(),
                Random::value<unsigned long long>(),

                Random::value<float>(),
                Random::value<double>(),
                // Random::value<long double>(),
                "Hello, char world!",
                u"Hello, char16 world!",
                U"Hello, char32 world!"
            };
        }
    };
}

template<>
class bio::io::Serializable<bio::tests::util::Output, bio::tests::util::Output::SerializerOptions> {
public:
    using Type = bio::tests::util::Output;
    using Options = bio::tests::util::Output::SerializerOptions;

    static void serialize(const bio::tests::util::Output &output, WritableBufferLike auto &writable, const bio::tests::util::Output::SerializerOptions &options) {
        writable.write(output.b, options.byteOrder);
        writable.write(output.c, options.byteOrder);
        writable.write(output.uc, options.byteOrder);
        writable.write(output.s, options.byteOrder);
        writable.write(output.us, options.byteOrder);
        writable.write(output.i, options.byteOrder);
        writable.write(output.ui, options.byteOrder);
        writable.write(output.l, options.byteOrder);
        writable.write(output.ul, options.byteOrder);
        writable.write(output.ll, options.byteOrder);
        writable.write(output.ull, options.byteOrder);

        writable.write(output.f, options.byteOrder);
        writable.write(output.d, options.byteOrder);
        // writable.write(output.ld, options.byteOrder);

        writable.template writeString<char>(output.str, options.byteOrder, util::string::StringLengthEncoding::NULL_TERMINATE);
        writable.template writeString<char16_t>(output.str16, options.byteOrder, util::string::StringLengthEncoding::NULL_TERMINATE);
        writable.template writeString<char32_t>(output.str32, options.byteOrder, util::string::StringLengthEncoding::NULL_TERMINATE);
    }
};

template<>
class bio::io::Deserializable<bio::tests::util::Output, bio::tests::util::Output::SerializerOptions> {
public:
    using Type = bio::tests::util::Output;
    using Options = bio::tests::util::Output::SerializerOptions;

    static std::unique_ptr<bio::tests::util::Output> deserialize(ReadableBufferLike auto &readable, const bio::tests::util::Output::SerializerOptions &options) {
        std::unique_ptr<tests::util::Output> output = std::make_unique<tests::util::Output>();

        output->b = readable.template read<bool>(options.byteOrder);
        output->c = readable.template read<signed char>(options.byteOrder);
        output->uc = readable.template read<unsigned char>(options.byteOrder);
        output->s = readable.template read<signed short>(options.byteOrder);
        output->us = readable.template read<unsigned short>(options.byteOrder);
        output->i = readable.template read<signed int>(options.byteOrder);
        output->ui = readable.template read<unsigned int>(options.byteOrder);
        output->l = readable.template read<signed long>(options.byteOrder);
        output->ul = readable.template read<unsigned long>(options.byteOrder);
        output->ll = readable.template read<signed long>(options.byteOrder);
        output->ull = readable.template read<unsigned long>(options.byteOrder);

        output->f = readable.template read<float>(options.byteOrder);
        output->d = readable.template read<double>(options.byteOrder);
        // output->ld = readable.template read<long double>(options.byteOrder);

        // TODO turn into readStringWithLength
        output->str = readable.template readCharStringNullTerminated<char>();
        output->str16 = readable.template readStringWithLength<char16_t>(options.byteOrder, util::string::StringLengthEncoding::NULL_TERMINATE);
        output->str32 = readable.template readStringWithLength<char32_t>(options.byteOrder, util::string::StringLengthEncoding::NULL_TERMINATE);

        return std::move(output);
    }
};

#endif // BIO_OUTPUT_H