/// @file Logging.h
/// @brief This header defines a logging system interface by providing a callback for logging events.
/// @details The logging system uses a callback mechanism to notify the application of log events.
///          The callback is invoked with the verbosity level and the log message.
/// @date 2025
/// @author Michael Petersen

#pragma once

#include <functional>
#include <string>

namespace logging {
/// @brief Verbosity levels for logging events.
/// @details The verbosity levels are represented as characters for easy comparison.
enum class Verbosity : char { Trace = 'T', Debugging = 'D', Information = 'I', Warning = 'W', Error = 'E', Fatal = 'F', Off = 'O' };

/// @brief Callback function type for logging events.
/// @details The callback function takes a verbosity level and a log message as parameters.
using LogEvent = std::function<void(Verbosity verbosity, const std::string &message)>;
} // namespace logging