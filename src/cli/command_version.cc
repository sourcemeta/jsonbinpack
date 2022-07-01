#include "commands.h"
#include "version.h"
#include <iostream> // std::cout

auto sourcemeta::jsonbinpack::cli::version() -> int {
  std::cout << sourcemeta::jsonbinpack::VERSION << "\n";
  return 0;
}
