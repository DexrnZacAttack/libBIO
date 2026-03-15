//
// Created by DexrnZacAttack on 2/27/26 using zPc-i2.
//
#include "BinaryIO/Tests/Tests.h"

#include "BinaryIO/buffer/BinaryBuffer.h"
#include "BinaryIO/Exports.h"
#include "BinaryIO/Tests/util/Output.h"
#include "BinaryIO/Tests/util/Random.h"
#include "BinaryIO/buffer/SizedBinaryBuffer.h"
#include "BinaryIO/stream/BinaryInputStream.h"
#include "BinaryIO/stream/BinaryOutputStream.h"
#include "TestFramework/TestFramework.h"
#include "TestFramework/test/exception/TestFailedException.h"

#include <future>
#include <iostream>

#include <fstream>
#include <ranges>

bio::tests::util::Output leOutputPreset = bio::tests::util::Output::fromRandom();
bio::tests::util::Output beOutputPreset = bio::tests::util::Output::fromRandom();

std::array<unsigned char, sizeof(bio::tests::util::Output) + 800> leOutputArray {};
std::array<unsigned char, sizeof(bio::tests::util::Output) + 800> beOutputArray {};

std::array<unsigned char, std::numeric_limits<unsigned char>::max()> iteratorArray {};

uint8_t testArray[std::numeric_limits<unsigned char>::max()]{};
std::span testSpan(testArray);

int main() {
    std::cout << bio::bio_get_library_string() << std::endl;

    tfw::TestFramework::getInstance()->addTest("Little endian write to memory", [](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::BinaryBuffer out = bio::buffer::BinaryBuffer(leOutputArray);

        out.serialize<bio::tests::util::Output::Serializer>(leOutputPreset, bio::tests::util::Output::SerializerOptions {
            bio::util::ByteOrder::LITTLE
        });
    });

    tfw::TestFramework::getInstance()->addComparableTest("Little endian read from memory", leOutputPreset, [](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::BinaryBuffer in = bio::buffer::BinaryBuffer(leOutputArray);

        std::unique_ptr<bio::tests::util::Output> o = in.deserialize<bio::tests::util::Output::Deserializer>(bio::tests::util::Output::SerializerOptions {
            bio::util::ByteOrder::LITTLE
        });

        return *o.get();
    });

    tfw::TestFramework::getInstance()->addTest("Big endian write to memory", [](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::BinaryBuffer out = bio::buffer::BinaryBuffer(beOutputArray);

        out.serialize<bio::tests::util::Output::Serializer>(beOutputPreset, bio::tests::util::Output::SerializerOptions {
            bio::util::ByteOrder::BIG
        });
    });

    tfw::TestFramework::getInstance()->addComparableTest("Big endian read from memory", beOutputPreset, [](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::BinaryBuffer in = bio::buffer::BinaryBuffer(beOutputArray);

        auto out = in.deserialize<bio::tests::util::Output::Deserializer>(bio::tests::util::Output::SerializerOptions {
            bio::util::ByteOrder::BIG
        });

        return *out.get();
    });

    tfw::TestFramework::getInstance()->addTest("Little endian write to file", [](tfw::test::util::TestOutputLogger &output) {
        std::ofstream ofstream("bio_out_le.bin");
        bio::stream::BinaryOutputStream out(ofstream);

        out.serialize<bio::tests::util::Output::Serializer>(leOutputPreset, bio::tests::util::Output::SerializerOptions {
            bio::util::ByteOrder::LITTLE
        });
    });

    tfw::TestFramework::getInstance()->addComparableTest("Little endian read from file", leOutputPreset, [](tfw::test::util::TestOutputLogger &output) {
        std::ifstream ifstream("bio_out_le.bin");
        bio::stream::BinaryInputStream in = bio::stream::BinaryInputStream(
            ifstream);

        return *in.deserialize<bio::tests::util::Output::Deserializer>(bio::tests::util::Output::SerializerOptions {
            bio::util::ByteOrder::LITTLE
        }).get();
    });

    tfw::TestFramework::getInstance()->addTest("Big endian write to file", [](tfw::test::util::TestOutputLogger &output) {
        std::ofstream ofstream("bio_out_be.bin");
        bio::stream::BinaryOutputStream out =
            bio::stream::BinaryOutputStream(ofstream);

        out.serialize<bio::tests::util::Output::Serializer>(beOutputPreset, bio::tests::util::Output::SerializerOptions {
            bio::util::ByteOrder::BIG
        });
    });

    tfw::TestFramework::getInstance()->addComparableTest("Big endian read from file", beOutputPreset, [](tfw::test::util::TestOutputLogger &output) {
        std::ifstream ifstream("bio_out_be.bin");
        bio::stream::BinaryInputStream in = bio::stream::BinaryInputStream(
            ifstream);

        return *in.deserialize<bio::tests::util::Output::Deserializer>(bio::tests::util::Output::SerializerOptions {
            bio::util::ByteOrder::BIG
        }).get();
    });

    tfw::TestFramework::getInstance()->addTest("Sized iterating write", [](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::SizedBinaryBuffer out = bio::buffer::SizedBinaryBuffer(iteratorArray);

        // also works with stl foreach
        for (const auto &[idx, byte] : out | std::views::enumerate) {
            byte = idx;
        };

        //read
        for (const auto &[idx, byte] : out | std::views::enumerate) {
            if (byte != idx) {
                return tfw::test::result::TestResult(false, "Output does not match what was written in");
            }
        }

        return tfw::test::result::TestResult(true);
    });

    tfw::TestFramework::getInstance()->addTest("Sized iterating write over a span", [](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::SizedBinaryBuffer out = bio::buffer::SizedBinaryBuffer(testSpan);

        // also works with stl foreach
        for (const auto &[idx, byte] : out | std::views::enumerate) {
            byte = idx;
        };

        //read
        for (const auto &[idx, byte] : out | std::views::enumerate) {
            if (byte != idx) {
                return tfw::test::result::TestResult(false, "Output does not match what was written in");
            }
        }

        return tfw::test::result::TestResult(true);
    });

    tfw::TestFramework::getInstance()->addTest("Reading from an STL view", [](tfw::test::util::TestOutputLogger &output) {
        auto view = iteratorArray | std::views::take(5);
        bio::buffer::SizedBinaryBuffer out = bio::buffer::SizedBinaryBuffer(view);

        // also works with stl foreach
        for (const auto &[idx, byte] : out | std::views::enumerate) {
             if (byte != idx) {
                 return tfw::test::result::TestResult(false, "Output does not match what was written in");
             }
         }

        return tfw::test::result::TestResult(true);
    });

    tfw::TestFramework::getInstance()->run();

    return 0;
}