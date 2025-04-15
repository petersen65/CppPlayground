# CppPlayground
C++ Playground

### Ubuntu with Bash Command Prompt
cd CppPlayground
rm -rf build CMakeUserPresets.json

### Conan
conan install . --profile:all default --settings:all build_type=Debug --settings:all compiler.cppstd=23 --build missing
conan install . --profile:all default --settings:all build_type=Release --settings:all compiler.cppstd=23 --build missing

### CMake
cmake --preset conan-debug
cmake --preset conan-release
cmake --build --preset conan-debug
cmake --build --preset conan-release