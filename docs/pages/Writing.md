# Writing
### Types
**Buffer**
- BinaryBuffer   
- SizedBinaryBuffer

**Stream**
- BinaryOutputStream

### Functions
- `write<T>(T value)`: Write value with platform endian
- `write<T>(T value, ByteOrder endian)`: Write value with given endian 
- `writeLE<T>(T value)`: Write value as little endian
- `writeBE<T>(T value)`: Write value as big endian

## Example
```cpp
output.write<bool>(false);
output.write<std::int8_t>(-1);
output.write<std::uint8_t>(0);
output.write<std::int16_t>(-1);
output.write<std::uint16_t>(0);
output.write<std::int32_t>(-1);
output.write<std::uint32_t>(0);
output.write<std::int64_t>(-1);
output.write<std::uint64_t>(0);

// floating point
// the comments which show the written values have been modified to show the value in BE,
// as it's more familiar

output.write<float>(1.0f); // writes as 0x3F800000
output.write<double>(1.0); // writes as 0x3FF0000000000000
output.write<long double>(1.0); // not recommended! writes as 0x3FFF8000000000000000000000000000 (extra 6 bytes at the end due to padding)

// other primitives
output.writeString("Hello, world!", NULL_TERMINATE); // NULL_TERMINATE is true in this case

// specialized
output.writeInt24(-1); // writes as 0xFFFFFF
output.writeUint24(0xFFFFFF00); // writes as 0xFFFFFF
```