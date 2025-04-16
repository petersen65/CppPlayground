#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <map>

// function that takes an array as a parameter
void f([[maybe_unused]] int arr[])
{
    // arr is a pointer to the first element of the array
}

// function that takes a 2D array as a parameter
void g([[maybe_unused]] int arr[][2])
{
    // arr is a pointer to the first element of the 2D array
}

// function that takes a 3D array as a parameter
void h([[maybe_unused]] int arr[][2][5])
{
    // arr is a pointer to the first element of the 3D array
}

// function that takes a pointer as a parameter
void i([[maybe_unused]] int *ptr)
{
    // ptr is a pointer to an integer
}

// function that takes a reference as a parameter
void j([[maybe_unused]] int &ref)
{
    // ref is a reference to an integer
}

int main()
{
    // integer types
    [[maybe_unused]] int i = 42;                     // 32-bit signed integer
    [[maybe_unused]] unsigned int ui = 42;           // 32-bit unsigned integer
    [[maybe_unused]] long l = 42L;                   // 64-bit signed integer (on most platforms)
    [[maybe_unused]] unsigned long ul = 42UL;        // 64-bit unsigned integer (on most platforms)
    [[maybe_unused]] long long ll = 42LL;            // 64-bit signed integer
    [[maybe_unused]] unsigned long long ull = 42ULL; // 64-bit unsigned integer
    [[maybe_unused]] short s = 42;                   // 16-bit signed integer
    [[maybe_unused]] unsigned short us = 42;         // 16-bit unsigned integer

    // floating-point types
    [[maybe_unused]] float f = 3.14F;           // 32-bit floating-point
    [[maybe_unused]] double d = 3.14;           // 64-bit floating-point
    [[maybe_unused]] long double ld = 1.71e-4L; // 80-bit or 128-bit floating-point (platform-dependent)

    // character types
    [[maybe_unused]] char c = 'A';        // 8-bit character
    [[maybe_unused]] wchar_t wc = L'B';   // wide character, typically 16 or 32 bits, depending on the platform
    [[maybe_unused]] char8_t c8 = u8'C';  // 8-bit character (UTF-8)
    [[maybe_unused]] char16_t c16 = u'C'; // 16-bit character (UTF-16)
    [[maybe_unused]] char32_t c32 = U'D'; // 32-bit character (UTF-32)

    // C string literals
    [[maybe_unused]] const char *raw1 = R"(raw string literal)";
    [[maybe_unused]] const char *raw2 = R"Separator(raw string literal with embedded ")Separator";
    [[maybe_unused]] const char8_t *raw3 = u8R"(raw string literal with UTF-8)";
    [[maybe_unused]] const char16_t *raw4 = uR"(raw string literal with UTF-16)";
    [[maybe_unused]] const char32_t *raw5 = UR"(raw string literal with UTF-32)";

    // C string
    const int nameLen = 20;
    [[maybe_unused]] char name[nameLen] = "John Doe"; // C-style string (array of characters) with null terminator
    [[maybe_unused]] char *namePtr = name;            // pointer to the first character of the string
    [[maybe_unused]] char &nameRef = name[0];         // reference to the first character of the string

    // boolean type
    [[maybe_unused]] bool b = true; // 1-byte boolean

    // enum types (scoped and unscoped)
    enum class ColorClass
    {
        Red,
        Green,
        Blue
    };
    enum Color
    {
        Red,
        Green,
        Blue
    };
    [[maybe_unused]] ColorClass colorClass = ColorClass::Red;
    [[maybe_unused]] Color colorEnum = Red;

    // C arrays
    const int arrSize = 5;
    [[maybe_unused]] int arr[arrSize] = {1, 2, 3, 4, 5}; // fixed-size array
    [[maybe_unused]] int *dynamicArr = new int[arrSize]; // dynamic array
    [[maybe_unused]] int *ptr = arr;                     // pointer to the first element of the array
    [[maybe_unused]] int &ref = arr[0];                  // reference to the first element of the array
    [[maybe_unused]] double matrix[3][2] = {             // initializer list for C array
                                            {1.0, 2.0},
                                            {4.0, 5.0},
                                            {7.0, 8.0}}; // 2D array (matrix)
    delete[] dynamicArr;                                 // deallocate dynamic array
    dynamicArr = nullptr;                                // avoid dangling pointer

    // pointer types
    [[maybe_unused]] int m = 10;
    [[maybe_unused]] int *p = &m;        // pointer to an integer
    [[maybe_unused]] int **pp = &p;      // pointer to a pointer to an integer
    [[maybe_unused]] void *vp = nullptr; // generic pointer type
    int *a = nullptr;                    // nullptr is a null pointer constant
    if (a)                               // pointers are implicitly convertible to bool
        ;
    [[maybe_unused]] void (*fp)(int[]); // function pointer variable declaration
    fp = ::f;                           // use global scope resolution operator to avoid ambiguity with variable 'f'
    fp(arr);                            // call function through pointer

    // member pointer types
    struct S
    {
        int i;
        void f([[maybe_unused]] int arr[])
        {
            // function implementation
        }
    };
    [[maybe_unused]] int S::*pm = &S::i;            // pointer to member of 'S' variable declaration 'pm'
    [[maybe_unused]] void (S::*pmf)(int[]) = &S::f; // pointer to member function of 'S' declaration 'pmf'
    S is;                                           // instance of struct S
    is.*pm = 42;                                    // access member variable through pointer (dot star)
    (is.*pmf)(arr);                                 // call member function through pointer (dot star)
    S *ps = new S;                                  // dynamic instance of struct S
    ps->*pm = 42;                                   // access member variable through pointer (arrow star)
    (ps->*pmf)(arr);                                // call member function through pointer (arrow star)
    delete ps;                                      // deallocate dynamic instance of struct S
    ps = nullptr;                                   // avoid dangling pointer

    // lvalue (short for locator value) refers to an expression that has a name and a location (left side of an assignment)
    // xvalue (short for expiring value) refers to an expression that is about to be moved from (has name/location but is about to be moved, std::move(x))
    // prvalue (short for pure right-hand value) refers to an expression that is temporary (no name/location, 42, std::string("Hello"))
    // rvalue (short for right-hand value) refers to an expression that is temporary or expiring (right side of an assignment, prvalue + xvalue)
    // glvalue (short for generalized lvalue) refers to an expression that has a name and a location but might not be assignable (lvalue + xvalue)

    // lvalue reference is a reference that can bind to an lvalue: &
    // rvalue reference is a reference that can bind to an rvalue: &&

    // reference types
    [[maybe_unused]] int &lr = i;   // lvalue reference to an integer (reference to integer variable that has a name and a persistent location)
    [[maybe_unused]] int &&rr = 42; // rvalue reference to an integer (reference to a temporary integer literal that does not have a name or a location)

    // value construction and initialization
    [[maybe_unused]] int a1 = 42;                                                // value construction (copy initialization)
    [[maybe_unused]] int a2(42);                                                 // value construction (direct initialization, not recommended due to narrowing conversion)
    [[maybe_unused]] int a3{42};                                                 // value construction (uniform initialization, no narrowing conversion)
    [[maybe_unused]] int iarr[3]{1, 2, 3};                                       // C array initialization with initializer list (uniform initialization)
    [[maybe_unused]] std::array iarr2{1, 2, 3};                                  // C++ array initialization with initializer list (uniform initialization)
    [[maybe_unused]] std::vector ivec{1, 2, 3};                                  // C++ vector initialization with initializer list (uniform initialization)
    [[maybe_unused]] std::string str{"Hello"};                                   // C++ string initialization with initializer list (uniform initialization)
    [[maybe_unused]] std::map<std::string, int> imap = {{"one", 1}, {"two", 2}}; // C++ map initialization with initializer list (uniform initialization)

    // structured bindings (bind arrays, tuples/pairs, non-static public class attributes, and structs to variables)
    [[maybe_unused]] auto [x, y] = std::make_pair(1, 2); // structured binding declaration (C++17, references to temporary)
    [[maybe_unused]] auto [key, value] = *imap.begin();  // structured binding declaration (C++17, references to temporary)
    [[maybe_unused]] const auto [ca1, ca2, ca3] = iarr;     // structured binding declaration (C++17, const lvalues)

    std::cout << "Hello, C++ Playground!" << std::endl;
    return EXIT_SUCCESS;
}