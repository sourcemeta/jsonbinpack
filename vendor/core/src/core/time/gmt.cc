#include <sourcemeta/core/time.h>

#include <cassert>   // assert
#include <ctime>     // std::time_t, std::tm, std::gmtime, std::mktime, timegm
#include <iomanip>   // std::put_time, std::get_time
#include <sstream>   // std::ostringstream, std::istringstream
#include <stdexcept> // std::invalid_argument, std::runtime_error

#if defined(_MSC_VER)
#include <errno.h>
#endif

namespace {
constexpr auto FORMAT_GMT{"%a, %d %b %Y %H:%M:%S GMT"};
}

namespace sourcemeta::core {

auto to_gmt(const std::chrono::system_clock::time_point time) -> std::string {
  const std::time_t ctime = std::chrono::system_clock::to_time_t(time);
  std::tm buffer;
#if defined(_MSC_VER)
  if (gmtime_s(&buffer, &ctime) != 0) {
    throw std::runtime_error("Could not convert time point to GMT");
  }
#else
  if (gmtime_r(&ctime, &buffer) == nullptr) {
    throw std::runtime_error("Could not convert time point to GMT");
  }
#endif
  std::tm *parts = &buffer;
  assert(parts);
  std::ostringstream stream;
  stream << std::put_time(parts, FORMAT_GMT);
  return stream.str();
}

auto from_gmt(const std::string &time)
    -> std::chrono::system_clock::time_point {
  std::istringstream stream{time};
  std::tm parts = {};
  stream >> std::get_time(&parts, FORMAT_GMT);
  if (stream.fail()) {
    throw std::invalid_argument("Invalid GMT timestamp");
  }

#if defined(_MSC_VER)
  return std::chrono::system_clock::from_time_t(_mkgmtime(&parts));
#else
  return std::chrono::system_clock::from_time_t(timegm(&parts));
#endif
}

} // namespace sourcemeta::core
