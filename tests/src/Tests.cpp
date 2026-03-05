//
// Created by DexrnZacAttack on 2/27/26 using zPc-i2.
//
#include "BinaryIO/Tests/Tests.h"

#include "BinaryIO/Exports.h"
#include "BinaryIO/Tests/util/Output.h"
#include "BinaryIO/Tests/util/Random.h"
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

    tfw::TestFramework::getInstance()->addTest("Write Little Endian", [leOutputPreset](tfw::test::util::TestOutputLogger &output) {
        std::ofstream ofstream("bio_out_le.bin");
        bio::stream::BinaryOutputStream out(ofstream);

        out.writeLE<bio::tests::util::Output>(leOutputPreset);

        ofstream.close();
    });

    tfw::TestFramework::getInstance()->addComparableTest("Read Little Endian", leOutputPreset, [](tfw::test::util::TestOutputLogger &output) {
        std::ifstream ifstream("bio_out_le.bin");
        bio::stream::BinaryInputStream in = bio::stream::BinaryInputStream(
            ifstream);

        return in.readLE<bio::tests::util::Output>();
    });

    tfw::TestFramework::getInstance()->addTest("Write Big Endian", [beOutputPreset](tfw::test::util::TestOutputLogger &output) {
        std::ofstream ofstream("bio_out_be.bin");
        bio::stream::BinaryOutputStream out =
            bio::stream::BinaryOutputStream(ofstream);

        out.writeBE<bio::tests::util::Output>(beOutputPreset);

        ofstream.close();
    });

    tfw::TestFramework::getInstance()->addComparableTest("Read Big Endian", beOutputPreset, [](tfw::test::util::TestOutputLogger &output) {
        std::ifstream ifstream("bio_out_be.bin");
        bio::stream::BinaryInputStream in = bio::stream::BinaryInputStream(
            ifstream);

        return in.readBE<bio::tests::util::Output>();
    });

    tfw::TestFramework::getInstance()->run();

    return 0;
}