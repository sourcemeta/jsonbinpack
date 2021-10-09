// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#include <iostream>
#include "config.h"  // NOLINT(build/include) as this file is auto-generated.
#include "jsonbinpack/stream/base.h"

int main() {
  jsonbinpack::stream::hello();
  std::cout << JSONBINPACK_VERSION_MAJOR << std::endl;
  std::cout << JSONBINPACK_VERSION_MINOR << std::endl;
  std::cout << JSONBINPACK_VERSION_PATCH << std::endl;
}
