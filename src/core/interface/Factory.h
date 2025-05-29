/// @file Factory.h
/// @brief This header defines factory function templates for creating objects.
/// @details The factory provides functions to create shared and unique pointers to objects that implement a specific interface.
/// @remarks ARGS &&...args is a function parameter pack, which allows the function to accept any number of arguments of any type.
///          The expression std::forward<ARGS>(args) is a pack expansion pattern that expands to:
///            std::forward<ARGS[0]>(args0), ..., std::forward<ARGS[M]>(argsM) when placed into a context like a function call or comma fold.
///          The expression std::forward<ARGS>(args) is a pack expansion pattern because ... follows an expression that contains a parameter pack.
///          ... after the expression means: expand the pattern for each pair of ARGS[i] and args[i] in the pack.
///          Expansion happens when the pack is used, not declared.
///          std::forward is used to perfectly forward the arguments of the factory function to the constructor of T.
///          This allows the factory function to accept both lvalue and rvalue references and pass them to the constructor of T without unnecessary copies.
/// @date 2025
/// @author Michael Petersen

#pragma once

#include <concepts>
#include <memory>

namespace factory {
/// @brief Concept to check if a type is an abstract class.
/// @tparam T The type to check.
/// @details This concept checks if T is an abstract class, meaning it has at least one pure virtual function.
template <typename T>
concept AbstractClass = std::is_abstract_v<T>;

/// @brief Variadic function template to create a shared pointer to an object of type T that implements interface I.
/// @details ARGS &&...args is a function parameter pack of the same size as ARGS, and each element args[i] has type ARGS[i]&&.
/// @tparam I       The interface type that the object must implement
/// @tparam T       The concrete type of the object to create, which must derive from I
/// @tparam ...ARGS Declares template parameter pack of types for the constructor arguments of T
/// @param ...args  Declares function parameter pack, using forwarding references
/// @return         A shared pointer to an object of type I, created from the concrete type T
template <AbstractClass I, std::derived_from<I> T, typename... ARGS>
auto CreateShared(ARGS &&...args) -> std::shared_ptr<I> {
    return std::make_shared<T>(std::forward<ARGS>(args)...);
}

/// @brief Variadic function template to create a unique pointer to an object of type T that implements interface I.
/// @details ARGS &&...args is a function parameter pack of the same size as ARGS, and each element args[i] has type ARGS[i]&&.
/// @tparam I       The interface type that the object must implement
/// @tparam T       The concrete type of the object to create, which must derive from I
/// @tparam ...ARGS Declares template parameter pack of types for the constructor arguments of T
/// @param ...args  Declares function parameter pack, using forwarding references
/// @return         A unique pointer to an object of type I, created from the concrete type T
template <AbstractClass I, std::derived_from<I> T, typename... ARGS>
auto CreateUnique(ARGS &&...args) -> std::unique_ptr<I> {
    return std::make_unique<T>(std::forward<ARGS>(args)...);
}
} // namespace factory