// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#include "jsonbinpack/cli/command.h"

#include <iostream>

#include "config.h"  // NOLINT(build/include) as this file is auto-generated.

int jsonbinpack::cli::command::Version() {
  std::cout << JSONBINPACK_VERSION_MAJOR << "." << JSONBINPACK_VERSION_MINOR
            << "." << JSONBINPACK_VERSION_PATCH << "\n";
  return 0;
}
