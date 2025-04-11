#include <iostream>

int main()
{
    // character types
    [[maybe_unused]] char c = 'A';        // 8-bit character
    [[maybe_unused]] wchar_t wc = L'B';   // wide character, typically 16 or 32 bits, depending on the platform
    [[maybe_unused]] char8_t c8 = u8'C';  // 8-bit character (UTF-8)
    [[maybe_unused]] char16_t c16 = u'C'; // 16-bit character (UTF-16)
    [[maybe_unused]] char32_t c32 = U'D'; // 32-bit character (UTF-32)

    // string literals
    [[maybe_unused]] const char *raw1 = R"(raw string literal)";
    [[maybe_unused]] std::string raw2 = R"Separator(raw string literal with embedded ")Separator";
    [[maybe_unused]] const char8_t *raw3 = u8R"(raw string literal with UTF-8)";
    [[maybe_unused]] const char16_t *raw4 = uR"(raw string literal with UTF-16)";
    [[maybe_unused]] const char32_t *raw5 = UR"(raw string literal with UTF-32)";

    std::cout << "Hello, C++ Playground!" << std::endl;
    return 0;
}