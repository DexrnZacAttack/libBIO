//
// Created by DexrnZacAttack on 3/3/26 using zPc-i2.
//
#ifndef BIO_OUTPUT_H
#define BIO_OUTPUT_H
#include "BinaryIO/Tests/util/Random.h"

namespace bio::tests::util {
    //pack so it writes without padding
    #pragma pack(push, 1)
    struct Output {
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
        long double ld;

        bool operator==(const Output &) const = default;

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
                Random::value<long double>(),
            };
        }
    };
    #pragma pack(pop)
}

#endif // BIO_OUTPUT_H