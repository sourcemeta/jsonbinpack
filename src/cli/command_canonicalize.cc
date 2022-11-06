#include "commands.h"
#include "utils.h"
#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsontoolkit/json.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <iostream>   // std::cout
#include <sstream>    // std::ostringstream

static auto canonicalize_document_from_string(const std::string document)
    -> int {
  sourcemeta::jsontoolkit::JSON<std::string> schema{document};
  sourcemeta::jsonbinpack::canonicalize(schema);
  std::cout << schema.pretty() << "\n";
  return EXIT_SUCCESS;
}

auto sourcemeta::jsonbinpack::cli::canonicalize(
    const std::filesystem::path &schema_path) -> int {
  // TODO: If JSON could be initialized from an istream, then we could
  // pipe an istream of the file into JSON directly rather than converting
  // the entire input document into an std::string first.
  const std::string raw_schema{
      sourcemeta::jsonbinpack::cli::utils::read_file(schema_path)};
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
