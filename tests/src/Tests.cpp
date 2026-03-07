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

int main() {
    std::cout << bio::bio_get_library_string() << std::endl;

    bio::tests::util::Output leOutputPreset = bio::tests::util::Output::fromRandom();
    bio::tests::util::Output beOutputPreset = bio::tests::util::Output::fromRandom();

    std::array<unsigned char, sizeof(bio::tests::util::Output)> leOutputArray {};
    std::array<unsigned char, sizeof(bio::tests::util::Output)> beOutputArray {};

    std::array<unsigned char, std::numeric_limits<unsigned char>::max()> iteratorArray {};

    uint8_t testArray[std::numeric_limits<unsigned char>::max()]{};
    std::span testSpan(testArray);

    tfw::TestFramework::getInstance()->addTest("Little endian write to memory", [leOutputPreset, &leOutputArray](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::BinaryBuffer out = bio::buffer::BinaryBuffer(leOutputArray);

        out.writeLE<bio::tests::util::Output>(leOutputPreset);
    });

    tfw::TestFramework::getInstance()->addComparableTest("Little endian read from memory", leOutputPreset, [&leOutputArray](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::BinaryBuffer in = bio::buffer::BinaryBuffer(leOutputArray);

        return in.readLE<bio::tests::util::Output>();
    });

    tfw::TestFramework::getInstance()->addTest("Big endian write to memory", [beOutputPreset, &beOutputArray](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::BinaryBuffer out = bio::buffer::BinaryBuffer(beOutputArray);

        out.writeBE<bio::tests::util::Output>(beOutputPreset);
    });

    tfw::TestFramework::getInstance()->addComparableTest("Big endian read from memory", beOutputPreset, [&beOutputArray](tfw::test::util::TestOutputLogger &output) {
        bio::buffer::BinaryBuffer in = bio::buffer::BinaryBuffer(beOutputArray);

        return in.readBE<bio::tests::util::Output>(); // technically this writes the entire thing backwards, but this is just a test of the byte swapping.
    });

    tfw::TestFramework::getInstance()->addTest("Little endian write to file", [leOutputPreset](tfw::test::util::TestOutputLogger &output) {
        std::ofstream ofstream("bio_out_le.bin");
        bio::stream::BinaryOutputStream out(ofstream);

        out.writeLE<bio::tests::util::Output>(leOutputPreset);
    });

    tfw::TestFramework::getInstance()->addComparableTest("Little endian read from file", leOutputPreset, [](tfw::test::util::TestOutputLogger &output) {
        std::ifstream ifstream("bio_out_le.bin");
        bio::stream::BinaryInputStream in = bio::stream::BinaryInputStream(
            ifstream);

        return in.readLE<bio::tests::util::Output>();
    });

    tfw::TestFramework::getInstance()->addTest("Big endian write to file", [beOutputPreset](tfw::test::util::TestOutputLogger &output) {
        std::ofstream ofstream("bio_out_be.bin");
        bio::stream::BinaryOutputStream out =
            bio::stream::BinaryOutputStream(ofstream);

        out.writeBE<bio::tests::util::Output>(beOutputPreset);
    });

    tfw::TestFramework::getInstance()->addComparableTest("Big endian read from file", beOutputPreset, [](tfw::test::util::TestOutputLogger &output) {
        std::ifstream ifstream("bio_out_be.bin");
        bio::stream::BinaryInputStream in = bio::stream::BinaryInputStream(
            ifstream);

        return in.readBE<bio::tests::util::Output>();
    });

    tfw::TestFramework::getInstance()->addTest("Sized iterating write", [&iteratorArray](tfw::test::util::TestOutputLogger &output) {
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

    tfw::TestFramework::getInstance()->addTest("Sized iterating write over a span", [&testSpan](tfw::test::util::TestOutputLogger &output) {
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

    tfw::TestFramework::getInstance()->addTest("Reading from an STL view", [&iteratorArray](tfw::test::util::TestOutputLogger &output) {
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