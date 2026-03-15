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
[Read the documentation](https://libbio.dexrn.me/pages.html)

| Page                                                  | Description                                                            |
|-------------------------------------------------------|------------------------------------------------------------------------|
| [Reading](docs/pages/Reading.md)                      | Reading from a stream/buffer                                           |
| [Writing](docs/pages/Writing.md)                      | Writing to a stream/buffer                                             |
| [Serialization](docs/pages/Serialization.md)          | Serializing structures, creating your own serializers                  |
| [Deserialization](docs/pages/Deserialization.md)      | Deserializing structures, creating your own deserializers              |
| [Undefined Behavior](docs/pages/UndefinedBehavior.md) | Common actions which may cause bugs/unintended long debugging sessions |

## Installation

### CMakeLists

```cmake
# can be CPP14+
# we'll use CPP20 for this example
set(CMAKE_CXX_STANDARD 20)

# Import FetchContent (remove if already included)
include(FetchContent)

# Grab from the repo
FetchContent_Declare(
        bio
        GIT_REPOSITORY https://codeberg.org/Dexrn/libBIO.git
        GIT_TAG 3.3.0
)
# Make it "available" (afaik lets you access vars)
FetchContent_MakeAvailable(bio)

# The library CMakeLists creates a target for each supported CPP version
# which are: 14, 17, 20, 23
#
# There's also the regular 'bio' target, but it might not use the correct CPP version.

# Link against it
target_link_libraries(MyProj PRIVATE bio-cpp20)
# You can also link against the static version if you wish
target_link_libraries(MyProj PRIVATE bio-static-cpp20)
```

## TODO
- [X] Allow user to specialize a custom read and write function for their class
  - I believe we can specialize read/write with a custom class type for this
  - Ideally, it should be as simple as calling `buf.read<T>` after specialization
  - The user impl could have it call `buf.read<T>` internally and create a struct based off those values, as commonly seen in many implementations.
- [X] Improve string reading/writing
  - [X] Allow for writing const char *, const char16_t *, const char32_t *, etc.
  - [ ] Allow for getting a fast reference view of the string
    - This string would be very temporary, as it would be invalid as soon as the data pointer which the buffer holds is deleted/invalidated 
    - Ideally, return an `std::string_view` that views over the string in data 
  - [ ] Add support for surrogates when doing `char16_t` conversions
    - Still need to look into whether `char16_t[]` allows for surrogates