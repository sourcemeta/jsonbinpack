#include "commands.h"

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // std::cerr

static const char *USAGE_DETAILS = R"EOF(
   version                     Print version information and quit.

   help                        Print this help information and quit.

   canonicalize [schema.json]  Canonicalize a given JSON Schema definition
                               and print the result to stdout. If a path to
                               a schema is not provided, the schema will
                               be read from standard input.

   compile [schema.json]       Compile a given JSON Schema definition
                               into an encoding schema and print the result to
                               stdout. If a path to a schema is not provided,
                               the schema will be read from standard input.
)EOF";

auto sourcemeta::jsonbinpack::cli::help(const std::string &program) -> int {
  std::clog << "Usage: " << program << " <command> [arguments...]\n";
  std::clog << USAGE_DETAILS;
  return EXIT_SUCCESS;
}
