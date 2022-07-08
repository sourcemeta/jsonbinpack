#include "commands.h"
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <fstream>  // std::ifstream
#include <iostream> // std::cout

// Heavily inspired by https://stackoverflow.com/a/116220
static auto read_file(const std::filesystem::path path) -> std::string {
  constexpr std::size_t buffer_size{4096};
  std::ifstream stream{path.string()};
  stream.exceptions(std::ios_base::badbit);
  std::string buffer(buffer_size, '\0');
  std::string output;
  while (stream.read(&buffer[0], buffer_size)) {
    output.append(buffer, 0,
                  static_cast<std::string::size_type>(stream.gcount()));
  }
  return output.append(buffer, 0,
                       static_cast<std::string::size_type>(stream.gcount()));
}

// TODO: Add an overload without a path that reads from stdin
auto sourcemeta::jsonbinpack::cli::canonicalize(const std::string &schema_path)
    -> int {
  const std::string raw_schema{read_file(schema_path)};
  sourcemeta::jsontoolkit::JSON<std::string> schema{raw_schema};
  sourcemeta::jsonbinpack::canonicalize(schema);
  std::cout << schema.pretty() << "\n";
  return 0;
}
