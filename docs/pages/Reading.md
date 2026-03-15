# Reading
### Types
**Buffer**
- BinaryBuffer
- SizedBinaryBuffer

**Stream**
- BinaryInputStream

### Functions
- `read<T>()`: Read value with platform endian
- `read<T>(ByteOrder endian)`: Read value with given endian
- `readLE<T>()`: Read value as little endian
- `readBE<T>()`: Read value as big endian

## Example
```cpp
bool b = buf.read<bool>();
std::int8_t i8 = buf.read<std::int8_t>();
std::uint8_t u8 = buf.read<std::uint8_t>();
std::int16_t i16 = buf.read<std::int16_t>();
std::uint16_t u16 = buf.read<std::uint16_t>();
std::int32_t i32 = buf.read<std::int32_t>();
std::uint32_t u32 = buf.read<std::uint32_t>();
std::int64_t i64 = buf.read<std::int64_t>();
std::uint64_t u64 = buf.read<std::uint64_t>();

// floating point
float f = buf.read<float>();
double d = buf.read<double>();
double ld = buf.read<long double>(); // not recommended

// other primitives
std::string str = buf.readString(sizeof("Hello, world!")); // reads string with given size
std::string ntstr = buf.readStringNT(); // reads string until 0x00 is hit (null terminated)

// specialized
std::int32_t i24 = buf.readInt24(); // reads into int32_t cuz there is no int24_t primitve
std::uint32_t u24 = buf.readUint24(); // reads into uint32_t cuz there is no uint24_t primitve
```