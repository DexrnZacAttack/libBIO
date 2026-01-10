# libBIO~~HAZARD~~ (BinaryIO)

A "Simple" C++ Binary IO library

> [!IMPORTANT]
> Pull Requests and Issues are only accepted on the [Codeberg repo](https://codeberg.org/Dexrn/libBIO).

## Usage

### CMakeLists

```cmake
# Import FetchContent (remove if already included)
include(FetchContent)

# Grab from the repo
FetchContent_Declare(
        BIO
        GIT_REPOSITORY https://github.com/DexrnZacAttack/libBIO.git
        GIT_TAG main
)
# Make it "available" (afaik lets you access vars)
FetchContent_MakeAvailable(BIO)

# Link against it
target_link_libraries(MyProj PRIVATE BIO)
# You can also link against the static version if you wish
target_link_libraries(MyProj PRIVATE BIO-Static)
```