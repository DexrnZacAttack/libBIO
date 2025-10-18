# libBIO~~HAZARD~~ (BinaryIO)
A "Simple" C++ Binary IO library

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
```