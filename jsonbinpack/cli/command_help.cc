// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#include "jsonbinpack/cli/command.h"

#include <iostream>

int jsonbinpack::cli::command::Help(const char* const program_path) {
  std::cerr << "Usage: " << program_path << " <command> [options...]\n\n"
            << "Commands:\n"
            << "    help             Print this help page and exit\n"
            << "    version          Print the version and exit\n";
  return 0;
}
