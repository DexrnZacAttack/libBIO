# BinaryBuffer {#binarybuffer}
\sa \ref bio::buffer::BinaryBuffer "The class definition for BinaryBuffer"

\brief `BinaryBuffer` is just a view over an existing buffer, unless constructed with std::size_t.

You may create a `BinaryBuffer` with any of the following types:
- [uint8_t *](\ref bio::buffer::BinaryBuffer::BinaryBuffer(uint8_t *input))
- [std::vector<uint8_t>](\ref bio::buffer::BinaryBuffer::BinaryBuffer(std::vector<uint8_t> &input))
- [std::array<uint8_t, Size>](\ref bio::buffer::BinaryBuffer::BinaryBuffer(std::array<uint8_t, Size> &input))
- [std::span<uint8_t>](\ref bio::buffer::BinaryBuffer::BinaryBuffer(std::span<uint8_t> &input))
- [std::size_t](\ref bio::buffer::BinaryBuffer::BinaryBuffer(size_t size))
    - By default, `BinaryBuffer` is simply a view over a pointer, however this constructor has it create its own array

Example with uint8_t*
```cpp
#include <BinaryIO/buffer/BinaryBuffer.h>
#include <iostream>
#include <cstdint>

int main() {
    constexpr std::size_t SIZE = sizeof(int) + sizeof(long long);
    uint8_t *myData = new uint8_t[SIZE]{};
    
    bio::buffer::BinaryBuffer buf = bio::buffer::BinaryBuffer(myData); // now you have a buffer
    
    buf.writeLE<int>(1); // write little endian integer
    buf.writeBE<long long>(-1); // write big endian long long
    
    for (size_t i = 0; i < SIZE; i++) {
        std::cout << (int)buf->readByte(); // print each byte in the buffer
    }
    
    return 0;
}
```