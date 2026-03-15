# Deserialization
\brief For writing your own structure deserializers, you may specialize the `bio::io::Deserializable` class.

> [!NOTE]
> This example only works for C++20, however the class is still usable on earlier versions, albeit slightly harder to use as it doesn't expose `bio::io::interfaces::ISeekable`.

## Example
```cpp
#include <BinaryIO/io/Serializable.h>

// for example showing how to use deserializer with BinaryInputStream
#include <BinaryIO/buffer/BinaryInputStream.h>
#include <iostream>

// define struct that we want to deserialize
struct MyStructure {
    using Deserializer = bio::io::Deserializable<MyStructure, void>;

    int i;
    long long l;
    std::string s;
};

// specialize bio::io::Deserializable
template<>
class bio::io::Deserializable<MyStructure, void> {
public:
    using Type = MyStructure;
    using Options = void; // allows us to call deserialize without an options arg.

    static std::unique_ptr<MyStructure> deserialize(ReadableBufferLike auto &readable) {    
        int i = readable.read<int>();
        long long l = readable.read<long long>();
        std::string s = readable.readStringNT();
        
        return std::make_unique<MyStructure>(MyStructure { i, l, s });
    }
};

int main() {
    std::ifstream is("MyStructure.dat");
    bio::stream::BinaryInputStream bis(os); // can also use BinaryBuffer
    
    std::unique_ptr<MyStructure> s = bos.deserialize<MyStructure::Deserializer>(/* options, if present */);
    // or, optionally:
    std::unique_ptr<MyStructure> s = MyStructure::Deserializer::deserialize(bos, /* options, if present */);

    // Now your structure has been deserialized into s, and you can do whatever you wish with it.

    return 0;
}

```