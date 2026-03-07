# libBIO~~HAZARD~~ (BinaryIO)
<a href="https://codeberg.org/Dexrn/libBIO">
    <img alt="codeberg-plural" height="56" src="https://cdn.jsdelivr.net/npm/@intergrav/devins-badges@3/assets/cozy-minimal/social/codeberg-plural_vector.svg">
</a>
<a href="https://libbio.dexrn.me">
    <img alt="ghpages" height="56" src="https://cdn.jsdelivr.net/npm/@intergrav/devins-badges@3/assets/cozy-minimal/documentation/ghpages_vector.svg">
</a>
<a href="https://github.com/DexrnZacAttack/libBIO">
    <img alt="github" height="40" src="https://cdn.jsdelivr.net/npm/@intergrav/devins-badges@3/assets/compact-minimal/available/github_vector.svg">
</a>

A Simple C++ IO library

> [!IMPORTANT]
> Pull Requests and Issues are only accepted on the [Codeberg repo](https://codeberg.org/Dexrn/libBIO).

## Usage

### CMakeLists

```cmake
# Import FetchContent (remove if already included)
include(FetchContent)

# Grab from the repo
FetchContent_Declare(
        bio
        GIT_REPOSITORY https://codeberg.org/Dexrn/libBIO.git
        GIT_TAG 3.1.0
)
# Make it "available" (afaik lets you access vars)
FetchContent_MakeAvailable(bio)

# Link against it
target_link_libraries(MyProj PRIVATE bio)
# You can also link against the static version if you wish
target_link_libraries(MyProj PRIVATE bio-static)
```

### BinaryBuffer
`BinaryBuffer` is just a view over an existing buffer, unless constructed with std::size_t.

You may create a `BinaryBuffer` with any of the following types:
 - `uint8_t *`
 - `std::vector<uint8_t>`
 - `std::array<uint8_t>`
 - `std::span<uint8_t>`
 - `std::size_t`
   - By default, `BinaryBuffer` is simply a view over a pointer, however this constructor has it create its own array 
   
Example with uint8_t*
```cpp
uint8_t *myData = new uint8_t[8]{};

bio::buffer::BinaryBuffer buf = bio::buffer::BinaryBuffer(myData); // now you have a buffer
```
### SizedBinaryBuffer
`SizedBinaryBuffer` is like `BinaryBuffer`, however it also holds the size of the array, which allows for iteration, among other things.

You may create a `SizedBinaryBuffer` with any of the following types:
- `uint8_t *`
- `std::array<uint8_t>`
- `std::span<uint8_t>`
- `std::size_t`
    - By default, `SizedBinaryBuffer` is simply a view over a begin and end pointer, however this constructor has it create its own array

Example with uint8_t*
```cpp
uint8_t *myData = new uint8_t[8]{};

bio::buffer::SizedBinaryBuffer buf = bio::buffer::SizedBinaryBuffer(myData, 8); // now you have a sized buffer

// you can iterate over it too!
for (uint8_t &byte : buf) {
    // do something here
}
```

### Writing
```cpp
// alternatives:
// write<T>(T value, ByteOrder endian) - Write value as given endian/byte order
// writeLE<T>(T value) - Write value as little endian
// writeBE<T>(T value) - Write value as big endian

buf.write<bool>(false);
buf.write<std::int8_t>(-1);
buf.write<std::uint8_t>(0);
buf.write<std::int16_t>(-1);
buf.write<std::uint16_t>(0);
buf.write<std::int32_t>(-1);
buf.write<std::uint32_t>(0);
buf.write<std::int64_t>(-1);
buf.write<std::uint64_t>(0);

// floating point
// the comments which show the written values have been modified to show the value in BE,
// as it's more familiar

buf.write<float>(1.0f); // writes as 0x3F800000
buf.write<double>(1.0); // writes as 0x3FF0000000000000
buf.write<long double>(1.0); // writes as 0x3FFF8000000000000000000000000000 (extra 6 bytes at the end due to padding)

// other primitives
buf.writeString("Hello, world!", NULL_TERMINATE); // NULL_TERMINATE is true in this case

// specialized
buf.writeInt24(-1); // writes as 0xFFFFFF
buf.writeUint24(0xFFFFFF00); // writes as 0xFFFFFF
```

### Reading
```cpp
// alternatives:
// read<T>(ByteOrder endian) - Read value as given endian/byte order
// readLE<T>() - Read value as little endian
// readBE<T>() - Read value as big endian

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
double ld = buf.read<long double>();

// other primitives
std::string str = buf.readString(sizeof("Hello, world!")); // reads string with given size
std::string ntstr = buf.readStringNT(); // reads string until 0x00 is hit (null terminated)

// specialized
std::int32_t i24 = buf.readInt24(); // reads into int32_t cuz there is no int24_t primitve
std::uint32_t u24 = buf.readUint24(); // reads into uint32_t cuz there is no uint24_t primitve
```

### An example of undefined behavior
```cpp
// You can also specify other types to read/write, however the behavior is undefined.
// Additionally, byte order handling may flip the entire structure
buf.write<MyStruct>({ false, 0, 1l }) // {bool, int, long}

// An example of this undefined behavior:
struct AnotherStruct {
    const char *str;
}

buf.write<AnotherStruct>({ "Hello, world!" }); // Writes out the address of that const char *, instead of the string contents
```