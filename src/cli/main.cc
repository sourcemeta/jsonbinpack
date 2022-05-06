#include "version.h"
#include <iostream>
#include <sourcemeta/tracing.h>

auto main() -> int {
  SOURCEMETA_TRACE_EVENT("jsonbinpack", "cli_main");
  std::cout << "JSON BinPack" << std::endl;
  std::cout << sourcemeta::jsonbinpack::VERSION << std::endl;
  return 0;
}
