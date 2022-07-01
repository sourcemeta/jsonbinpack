#include "commands.h"
#include <iostream> // std::cerr

static const char *USAGE_DETAILS = R"EOF(
   version                     Print version information and quit.
   help                        Print this help information and quit.
   canonicalize <schema.json>  Canonicalize a given JSON Schema definition
                               and print the result to stdout.
)EOF";

auto sourcemeta::jsonbinpack::cli::help(const std::string &program) -> int {
  std::cerr << "Usage: " << program << " <command> [arguments...]\n";
  std::cerr << USAGE_DETAILS;
  return 0;
}
