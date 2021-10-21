// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#include <iostream>
#include <string>

#include "jsonbinpack/cli/command.h"

int main(int argc, char **argv) {
  // This means the user executed the tool without passing any argument,
  // in which case a non-zero exit code is more appropriate.
  if (argc <= 1) {
    jsonbinpack::cli::command::Help(argv[0]);
    return 1;
  }

  const std::string_view command{argv[1]};
  if (command == "version") {
    return jsonbinpack::cli::command::Version();
  } else if (command == "help") {
    return jsonbinpack::cli::command::Help(argv[0]);
  } else {
    std::cerr << "Unknown command: " << command << "\n";
    return 1;
  }
}
