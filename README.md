# CppPlayground
C++ Playground for learning C++ topics

### Conan Profiles
Profile are located under $HOME/.conan2/profiles/<os-compiler-cpu>

#### Windows with GCC 15.1
Install the following software packages under the PowerShell Terminal command prompt

    winget install --id Git.Git
    winget install --id Microsoft.VisualStudioCode
    winget install --id Ninja-build.Ninja
    winget install --id Python.Python.3.13
    winget install --id BrechtSanders.WinLibs.POSIX.UCRT

    pip install --upgrade pip
    pip install cmake coloredlogs cmake_format conan

    code --install-extension ms-vscode.cpptools-extension-pack
    code --install-extension cheshirekow.cmake-format
    code --install-extension github.codespaces
    code --install-extension github.copilot
    code --install-extension github.copilot-chat
    code --install-extension vscode-icons-team.vscode-icons

Create virus directory exclusion on Windows Defender for this directory

    AppData\Local\Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\

Create profile file "$env:HOME/.conan2/profiles/windows_gcc-15_amd64"

    Filename: windows_gcc-15_amd64

    [settings]
    arch=x86_64
    build_type=Debug
    compiler=gcc
    compiler.cppstd=26
    compiler.cstd=23
    compiler.libcxx=libstdc++11
    compiler.version=15.1
    os=Windows

### PowerShell Command Prompt
Set-Location -Path CppPlayground  
Remove-Item -Path build,CMakeUserPresets.json -Recurse -Force

### Bash or Zsh Command Prompt
cd CppPlayground  
rm -rf build CMakeUserPresets.json

### Conan on Windows
conan install . --profile:all windows_gcc-15_amd64 --settings:all build_type=Debug --build missing  
conan install . --profile:all windows_gcc-15_amd64 --settings:all build_type=Release --build missing

### CMake
cmake --preset conan-debug  
cmake --preset conan-release  
cmake --build --preset conan-debug  
cmake --build --preset conan-release
