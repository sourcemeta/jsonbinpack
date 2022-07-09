#include "commands.h"
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <fstream>  // std::ifstream
#include <iostream> // std::cout
#include <sstream>  // std::ostringstream

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

static auto canonicalize_document_from_string(const std::string document)
    -> int {
  sourcemeta::jsontoolkit::JSON<std::string> schema{document};
  sourcemeta::jsonbinpack::canonicalize(schema);
  std::cout << schema.pretty() << "\n";
  return 0;
}

auto sourcemeta::jsonbinpack::cli::canonicalize(const std::string &schema_path)
    -> int {
  // TODO: If JSON could be initialized from an istream, then we could
  // pipe an istream of the file into JSON directly rather than converting
  // the entire input document into an std::string first.
  const std::string raw_schema{read_file(schema_path)};
  return canonicalize_document_from_string(raw_schema);
}

auto sourcemeta::jsonbinpack::cli::canonicalize() -> int {
  std::string line;
  std::ostringstream stream;
  while (std::getline(std::cin, line)) {
    stream << line << "\n";
  }

  return canonicalize_document_from_string(stream.str());
}
