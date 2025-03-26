# CppLsegPlayground
C++ LSEG Playground

### Ubuntu with Bash Command Prompt
cd CppLsegPlayground
rm -rf build CMakeUserPresets.json

### Conan
conan install . -s build_type=Debug -s compiler.cppstd=23 -b missing
conan install . -s build_type=Release -s compiler.cppstd=23 -b missing

### CMake
cmake --preset conan-debug
cmake --preset conan-release
cmake --build --preset conan-debug
cmake --build --preset conan-release