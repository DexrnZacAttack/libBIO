# SizedBinaryBuffer {#sizedbinarybuffer}
\sa \ref bio::buffer::SizedBinaryBuffer "The class definition for SizedBinaryBuffer"

\brief `SizedBinaryBuffer` is like `BinaryBuffer`, however it also holds the size of the array, which allows for iteration, among other things.

You may create a `SizedBinaryBuffer` with any of the following types:
- [uint8_t *input, size_t size](\ref bio::buffer::SizedBinaryBuffer::SizedBinaryBuffer(uint8_t *input, size_t size))
- [std::array<uint8_t, Size>](\ref bio::buffer::SizedBinaryBuffer::SizedBinaryBuffer(std::array<uint8_t, Size> &input))
- [std::span<uint8_t>](\ref bio::buffer::SizedBinaryBuffer::SizedBinaryBuffer(std::span<uint8_t> &input))
- [std::size_t](\ref bio::buffer::SizedBinaryBuffer::SizedBinaryBuffer(size_t size))
    - By default, `SizedBinaryBuffer` is simply a view over a begin and end pointer, however this constructor has it create its own array

## Usage
Example with uint8_t*
```cpp
#include <BinaryIO/buffer/SizedBinaryBuffer.h>
#include <iostream>
#include <cstdint>

int main() {
    constexpr std::size_t SIZE = sizeof(int) + sizeof(long long);
    uint8_t *myData = new uint8_t[SIZE]{};
    
    bio::buffer::SizedBinaryBuffer buf = bio::buffer::SizedBinaryBuffer(myData, SIZE); // now you have a sized buffer
    
    buf.writeLE<int>(1); // write little endian integer
    buf.writeBE<long long>(-1); // write big endian long long
    
    // you can iterate over the buffer too!
    for (uint8_t byte : buf) {
        std::cout << (int)byte; // print each byte in the buffer
    }
    
    return 0;
}
```