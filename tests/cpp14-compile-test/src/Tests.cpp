//
// Created by DexrnZacAttack on 2/27/26 using zPc-i2.
//
#include "BinaryIO/buffer/BinaryBuffer.h"
#include "BinaryIO/Exports.h"
#include "BinaryIO/buffer/SizedBinaryBuffer.h"

#include <array>
#include <iostream>
#include <limits>

int main() {
    std::cout << bio::bio_get_library_string() << std::endl;

    std::array<unsigned char, std::numeric_limits<unsigned char>::max()> arr {};
    {
        bio::buffer::SizedBinaryBuffer out = bio::buffer::SizedBinaryBuffer(arr);

        //write
        for (int i = 0; i < out.size(); i++) {
            out.writeLE<uint8_t>(i); // jank lol
        };
    }

    {
        bio::buffer::SizedBinaryBuffer in = bio::buffer::SizedBinaryBuffer(arr);

        //read
        for (int i = 0; i < in.size(); i++) {
            if (in.readLE<uint8_t>() != i) {
                throw std::runtime_error("Output does not match what was written in");
            }
        }
    }

    return 0;
}