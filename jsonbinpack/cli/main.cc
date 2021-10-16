// Copyright (c) 2021 Juan Cruz Viotti. All rights reserved.

#include <string>

#include "jsonbinpack/cli/command_help.h"
#include "jsonbinpack/cli/command_version.h"

static const char *kCommandVersion = "version";

int main(int argc, char **argv) {
  const std::string_view command{argc <= 1 ? "help" : argv[1]};
  if (command == kCommandVersion) {
    return jsonbinpack::cli::command::Version();
  }

  const int code = jsonbinpack::cli::command::Help(argv[0]);
  // This means the user executed the tool without passing any argument,
  // in which case a non-zero exit code is more appropriate.
  if (code == 0 && argc == 1) {
    return 1;
  }

  return code;
}
