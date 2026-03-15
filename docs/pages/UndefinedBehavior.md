# An example of undefined behavior
You can also specify other types to read/write, however the behavior is undefined.

Byte order handling will usually end up flipping the entire structure
```cpp
// Writing this with opposite endian will end up flipping the entire structure.
buf.write<MyStruct>({ false, 0, 1l }) // {bool, int, long}

// An example of this undefined behavior:
struct AnotherStruct {
    const char *str;
}

buf.write<AnotherStruct>({ "Hello, world!" }); // Writes out the address of that const char *, instead of the string contents
```