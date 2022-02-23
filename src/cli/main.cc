#include "version.h"
#include <iostream>

auto main() -> int {
  std::cout << "JSON BinPack" << std::endl;
  std::cout << sourcemeta::jsonbinpack::VERSION << std::endl;
  return 0;
}
