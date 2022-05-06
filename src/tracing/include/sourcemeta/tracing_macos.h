#ifndef SOURCEMETA_TRACING_TRACING_MACOS_H_
#define SOURCEMETA_TRACING_TRACING_MACOS_H_

#ifdef __APPLE__
#include <os/log.h>
#include <os/signpost.h>
#include <string>
#include <unordered_map>

namespace sourcemeta::tracing {
std::unordered_map<std::string, os_log_t> subsystems;
}

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define __SOURCEMETA_TRACE_ENSURE_SUBSYSTEM(subsystem)                         \
  {                                                                            \
    if (sourcemeta::tracing::subsystems.find(subsystem) ==                     \
        sourcemeta::tracing::subsystems.end()) {                               \
      sourcemeta::tracing::subsystems.insert(                                  \
          {subsystem, os_log_create("com.sourcemeta." subsystem,               \
                                    OS_LOG_CATEGORY_POINTS_OF_INTEREST)});     \
    }                                                                          \
  };
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define __SOURCEMETA_TRACE_GET_SUBSYSTEM(subsystem)                            \
  sourcemeta::tracing::subsystems.at(subsystem)
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SOURCEMETA_TRACE_EVENT(subsystem, event)                               \
  {                                                                            \
    __SOURCEMETA_TRACE_ENSURE_SUBSYSTEM(subsystem);                            \
    os_signpost_event_emit(__SOURCEMETA_TRACE_GET_SUBSYSTEM(subsystem),        \
                           OS_SIGNPOST_ID_EXCLUSIVE, (event), "");             \
  };

#endif
#endif
