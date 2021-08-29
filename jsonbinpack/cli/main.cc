#include <iostream>
#include <jsonbinpack/stream/base.h>
#include "config.h"

int main() {
  jsonbinpack::stream::hello();
  std::cout << JSONBINPACK_VERSION_MAJOR << std::endl;
  std::cout << JSONBINPACK_VERSION_MINOR << std::endl;
  std::cout << JSONBINPACK_VERSION_PATCH << std::endl;
}
