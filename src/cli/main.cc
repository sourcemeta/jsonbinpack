#include "version.h"
#include <exception> // std::exception
#include <iostream>  // std::cout, std::cerr

auto main() -> int {
  try {
    std::cout << "JSON BinPack" << std::endl;
    std::cout << sourcemeta::jsonbinpack::VERSION << std::endl;
    return 0;
  } catch (const std::exception &error) {
    std::cerr << "Error: " << error.what() << "\n";
    return 1;
  }
}
