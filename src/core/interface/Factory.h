/// @file Factory.h
/// @brief
/// @date 2025
/// @author Michael Petersen

#pragma once

#include <concepts>
#include <memory>

namespace factory {
template <typename I, std::derived_from<I> T, typename... ARGS>
auto CreateShared(ARGS &&...args) -> std::shared_ptr<I> {
    return std::make_shared<T>(std::forward<ARGS>(args)...);
}

template <typename I, std::derived_from<I> T, typename... ARGS>
auto CreateUnique(ARGS &&...args) -> std::unique_ptr<I> {
    return std::make_unique<T>(std::forward<ARGS>(args)...);
}
} // namespace factory