# Serialization
\brief For writing your own structure serializers, you may specialize the `bio::io::Serializable` class.

> [!NOTE]
> This example only works for C++20, however the class is still usable on earlier versions, albeit slightly harder to use as it doesn't expose `bio::io::interfaces::ISeekable`.

## Example
```cpp
#include <BinaryIO/io/Serializable.h>

// for example showing how to use serializer with BinaryOutputStream
#include <BinaryIO/buffer/BinaryOutputStream.h>
#include <iostream>

// define struct that we want to serialize
struct MyStructure {
    using Serializer = bio::io::Serializable<MyStructure, void>;

    int i;
    long long l;
    std::string s;
};

// specialize bio::io::Serializable
template<>
class bio::io::Serializable<MyStructure, void> {
public:
    using Type = MyStructure;
    using Options = void; // allows us to call serialize without an options arg.

    static void serialize(const MyStructure& structure, WritableBufferLike auto &writable) {
        writable.write<int>(structure.i);
        writable.write<long long>(structure.l);
        writable.writeString(structure.s, true);
    }
};

int main() {
    std::ofstream os("MyStructure.dat");
    bio::stream::BinaryOutputStream bos(os); // can also use BinaryBuffer
    
    MyStructure s {
        0,
        1,
        "Hello, world!"
    };
    
    bos.serialize<MyStructure::Serializer>(s, /* options, if present */);
    // or, optionally:
    MyStructure::Serializer::serialize(s, bos, /* options, if present */);

    return 0;
}

```