#include "commands.h"

#include <jsonbinpack/decoder/decoder.h>
#include <jsonbinpack/parser/parser.h>

#include <jsontoolkit/json.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <ios>        // std::ios_base
#include <iostream>   // std::cin, std::cout
#include <istream>    // std::basic_istream

template <typename CharT, typename Traits>
static auto decode_from_stream(const sourcemeta::jsontoolkit::JSON &schema,
                               std::basic_istream<CharT, Traits> &stream)
    -> int {
  // TODO: Run canonicalizer and mapper on the schema.
  // These components are vocabulary-aware, so they will
  // be a no-op if the schema is already an encoding schema.
  const sourcemeta::jsonbinpack::Encoding encoding{
      sourcemeta::jsonbinpack::parse(schema)};
  sourcemeta::jsonbinpack::Decoder decoder{stream};
  const sourcemeta::jsontoolkit::JSON result{decoder.decode(encoding)};
  sourcemeta::jsontoolkit::stringify(result, std::cout);
  return EXIT_SUCCESS;
}

auto sourcemeta::jsonbinpack::cli::decode(
    const std::filesystem::path &schema_path,
    const std::filesystem::path &data_path) -> int {
  std::ifstream schema_stream{schema_path};
  std::ifstream data_stream{data_path};
  schema_stream.exceptions(std::ios_base::badbit);
  data_stream.exceptions(std::ios_base::badbit);
  return decode_from_stream(sourcemeta::jsontoolkit::parse(schema_stream),
                            data_stream);
}

auto sourcemeta::jsonbinpack::cli::decode(
    const std::filesystem::path &schema_path) -> int {
  std::ifstream schema_stream{schema_path};
  schema_stream.exceptions(std::ios_base::badbit);
  return decode_from_stream(sourcemeta::jsontoolkit::parse(schema_stream),
                            std::cin);
}
