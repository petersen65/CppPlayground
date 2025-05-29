# CppPlayground
C++ Playground

### Ubuntu with Bash Command Prompt
cd CppPlayground
rm -rf build CMakeUserPresets.json

### Conan
conan install . --profile:all macos_gcc-15_arm64 --settings:all build_type=Debug --build missing
conan install . --profile:all macos_gcc-15_arm64 --settings:all build_type=Release --build missing

### CMake
cmake --preset conan-debug
cmake --preset conan-release
cmake --build --preset conan-debug
cmake --build --preset conan-release