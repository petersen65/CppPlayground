#include <array>
#include <chrono>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Account.h"
#include "distance/Distance.h"

using namespace banking;
using namespace unit;

// unnamed namespace for internal linkage (better alternative to static on global variables and functions)
// variables and functions declared in an unnamed namespace have internal linkage
// they are only visible within the translation unit (source file) where they are defined
namespace {
[[maybe_unused]] int internalVar = 42; // internal linkage variable
} // namespace

// function that takes an array as a parameter
// noexcept specification is used to indicate that the function does not throw exceptions
//   compiler can optimize the code better
//   the caller can assume that it doesn't need to handle exceptions
//   if the function does throw an exception, the caller should not handle it and the program will terminate
//
void f([[maybe_unused]] int arr[]) noexcept {
    // arr is a pointer to the first element of the array
}

// function that takes a 2D array as a parameter
// at compile time, the compiler knows that the function will throw an exception
void g([[maybe_unused]] int arr[][2]) noexcept(false) {
    // arr is a pointer to the first element of the 2D array
}

// function that takes a 3D array as a parameter
// at compile time, the compiler knows that the function will not throw an exception if the function "f" is noexcept
// the noexcept specification uses the "noexcept" operator to check if the function "f" is noexcept
void h([[maybe_unused]] int arr[][2][5]) noexcept(noexcept(f)) {
    // arr is a pointer to the first element of the 3D array
}

// function that takes a pointer as a parameter (with default value of nullptr)
void i([[maybe_unused]] int *ptr = nullptr) {
    // ptr is a pointer to an integer
}

// function that takes a reference as a parameter (with default value of 0)
void j([[maybe_unused]] const int &ref = {}) {
    // ref is a reference to an integer
}

int main() {
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
    enum class ColorClass { Red, Green, Blue };
    enum Color { Red, Green, Blue };
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
    if (a) {                             // pointers are implicitly convertible to bool
    }
    [[maybe_unused]] void (*fp)(int[]); // function pointer variable declaration
    fp = ::f;                           // use global scope resolution operator to avoid ambiguity with variable 'f'
    fp(arr);                            // call function through pointer

    // member pointer types
    struct S {
        int i;
        void f([[maybe_unused]] int arr[]) {
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
    [[maybe_unused]] int a1 = 42;               // value construction (copy initialization)
    [[maybe_unused]] int a2(42);                // value construction (direct initialization, not recommended due to narrowing conversion)
    [[maybe_unused]] int a3{42};                // value construction (uniform initialization, no narrowing conversion)
    [[maybe_unused]] int a4{};                  // value construction (uniform initialization, default value of type)
    [[maybe_unused]] int iarr[3]{1, 2, 3};      // C array initialization with initializer list (uniform initialization)
    [[maybe_unused]] std::array iarr2{1, 2, 3}; // C++ array initialization with initializer list (uniform initialization)
    [[maybe_unused]] std::vector ivec{1, 2, 3}; // C++ vector initialization with initializer list (uniform initialization)
    [[maybe_unused]] std::string str{"Hello"};  // C++ string initialization with initializer list (uniform initialization)
    [[maybe_unused]] std::map<std::string, int> imap = {{"one", 1}, {"two", 2}}; // C++ map initialization with initializer list (uniform initialization)

    // structured bindings (bind arrays, tuples/pairs, non-static public class attributes, and structs to variables)
    [[maybe_unused]] auto [x, y] = std::make_pair(1, 2); // structured binding declaration (C++17, references to temporary)
    [[maybe_unused]] auto [key, value] = *imap.begin();  // structured binding declaration (C++17, references to temporary)
    [[maybe_unused]] const auto [ca1, ca2, ca3] = iarr;  // structured binding declaration (C++17, const lvalues)

    // memory classes C++17:
    //   static, extern, mutable, register
    //   for local variables, global variables, attributes, functions, and methods
    //
    // qualifiers C++17:
    //   const, constexpr, inline, volatile
    //   for local variables, global variables, attributes, non-static methods, function parameters, and return values

    // type deduction with auto and decltype (auto type deduction is identical to template parameter type deduction)
    [[maybe_unused]] int tdi{5};       // explicit type from declaration
    [[maybe_unused]] auto tdi2 = 5;    // type deduction from explicit initializer (auto, removes qualifiers and references)
    [[maybe_unused]] decltype(tdi2) r; // type deduction from expression evaluation at compile time (decltype, keeps qualifiers and references)

    // runtime type information (RTTI)
    typedef IAccount Acc;
    using AccPtr = Acc *;
    using AccRef = Acc &;
    [[maybe_unused]] const std::type_info &ti = typeid(Acc); // get type information at runtime
    [[maybe_unused]] auto ti_name = ti.name();               // get type name as string
    [[maybe_unused]] auto ti_hash = ti.hash_code();          // get type hash code
    [[maybe_unused]] auto &ti2 = typeid(AccPtr);             // get type information for pointer
    [[maybe_unused]] auto &ti3 = typeid(AccRef);             // get type information for reference

    // exception handling
    try {
        // code that may throw an exception
        throw std::runtime_error("Error occurred"); // value construction of temporary exception object
    } catch (const std::exception &e) {
        // catch block for std::exception and derived classes
        // e is a constant reference to the exception object
        std::cerr << "Caught exception: " << e.what() << std::endl;
    } catch (...) {
        // catch block for all other exceptions
        std::cerr << "Caught unknown exception" << std::endl;
    }

    // type traits
    [[maybe_unused]] bool is_integral = std::is_integral<int>::value;               // check if type is integral
    [[maybe_unused]] bool is_floating_point = std::is_floating_point<float>::value; // check if type is floating point
    [[maybe_unused]] bool is_pointer = std::is_pointer<int *>::value;               // check if type is pointer
    [[maybe_unused]] bool is_reference = std::is_reference<int &>::value;           // check if type is reference

    // static assertions
    static_assert(std::is_integral<int>::value, "int is not an integral type");                // compile-time assertion
    static_assert(std::is_floating_point<float>::value, "float is not a floating point type"); // compile-time assertion
    static_assert(std::is_pointer<int *>::value, "int* is not a pointer type");                // compile-time assertion

    // using declarations and using statements
    using std::cout;                      // using declaration for std::cout
    using std::endl;                      // using declaration for std::endl
    using namespace std::string_literals; // using statement for string literals
    using namespace std::chrono_literals; // using statement for chrono literals

    // namespace alias
    namespace ns = std::chrono;                                        // namespace alias for std::chrono
    [[maybe_unused]] ns::duration<int> d1 = ns::seconds(5);            // duration of 5 seconds
    [[maybe_unused]] ns::duration<double> d2 = ns::milliseconds(1000); // duration of 1000 milliseconds

    // lambda functions
    // [binding] (parameters) -> return_type { body }
    //   binding: capture by value or reference ([=] for value, [&] for reference, [x] for x by value, [&x] for x by reference)
    //   parameters: input parameters (optional, can be omitted if no parameters)
    //   return_type: return type (optional, can be deduced, if deduced the arrow operator must be omitted)
    //   body: function body (optional, can be empty)
    //
    // the binding create a closure that can be described as a function object
    //   a closure is an object that captures the environment in which it was created
    //   the closure can be seen as struct on the stack with the captured variables as values or references
    [[maybe_unused]] auto noop = [] {}; // lambda function with no parameters and deduced return type "void" (no parentheses and no arrow operator)
    auto lambda = [](int x) -> long { return x * 2; };         // lambda function that takes an integer and returns its double as long
    [[maybe_unused]] long result = lambda(5);                  // call lambda function with argument 5
    constexpr auto add = [](auto x, auto y) { return x + y; }; // generic lambda function that takes two arguments and returns their sum (C++14)
    add(4, 5);                                                 // evaluate the lambda function at compile time
    add(i, i);                                                 // evaluate the lambda function at runtime

    // Generated class member functions by the compiler:
    //   C++ 03 :
    //   1) Implicitly-declared Constructor with no args declared as defaulted (generated only if no constructor is declared by user)
    //   2) Implicitly-declared Copy Constructor (generated only if 5, 6 not declared by user)
    //   3) Implicitly-declared Copy Assignment operator (generated only if 5, 6 not declared by user)
    //   4) Implicitly-declared Destructor declared as defaulted (generated if no destructor is declared by user)
    //
    //   Since C++ 11:
    //   5) Move Constructor (generated only if 2, 3, 4, 6 not declared by user)
    //   6) Move Assignment Operator (generated only if 2, 3, 4, 5 not declared by user)

    // In C++11,
    //   a) Implicitly-declared Copy Constructor: deprecated if the class has a user-declared copy assignment operator or a user-declared destructor
    //   b) Implicitly-declared Copy Assignment operator: see (a)
    //   c) For user-declared Copy/Move Constructors and user-declared Copy/Move Assignments, always declare both Constructors and Assignments
    //   d) In practice, implicit destructors are noexcept unless the class is "poisoned" by a base or member whose destructor is noexcept(false)

    // Smart pointers
    //   std::unique_ptr: exclusive ownership of a resource (no copy, only move)
    //   std::shared_ptr: shared ownership of a resource (reference counting)
    std::unique_ptr<int> uptr = std::make_unique<int>(42);
    std::shared_ptr account = createAccount(1, 100.0);
    account->deposit(50.0);

    std::cout << "Hello, C++ Playground!" << std::endl;
    return EXIT_SUCCESS;
}