//
// Created by DexrnZacAttack on 3/3/26 using zPc-i2.
//
#ifndef BIO_RANDOM_H
#define BIO_RANDOM_H
#include <concepts>
#include <random>

namespace bio::tests::util {
    template <typename T>
    concept Randomizable = std::integral<T> || std::floating_point<T> || std::is_same_v<T, bool>;

    class Random {
    public:
        Random() = delete;

        template <Randomizable T>
        static T value(T min, T max) {
            std::random_device rd;
            std::mt19937 e{rd()};

            if constexpr (std::floating_point<T>) {
                std::uniform_real_distribution<T> dist{min, max};

                return dist(e);
            } else if constexpr (std::is_same_v<T, bool>) {
                std::bernoulli_distribution dist;

                return dist(e);
            } else if constexpr (std::integral<T>) {
                std::uniform_int_distribution<T> dist{min, max};

                return dist(e);
            }

            return 0;
        }

        template <Randomizable T>
        static T value() {
            return value(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
        }
    };
}

#endif // BIO_RANDOM_H