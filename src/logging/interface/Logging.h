#pragma once

#include <functional>
#include <string>

namespace logging {
enum class Verbosity : char { Trace = 'T', Debugging = 'D', Information = 'I', Warning = 'W', Error = 'E', Fatal = 'F', Off = 'O' };
using LogEvent = std::function<void(Verbosity, const std::string &)>;
} // namespace logging