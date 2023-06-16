#include "commands.h"
#include "defaults.h"
#include "resolver.h"

#include <jsonbinpack/canonicalizer/canonicalizer.h>
#include <jsonbinpack/decoder/decoder.h>
#include <jsonbinpack/mapper/mapper.h>
#include <jsonbinpack/parser/parser.h>

#include <jsontoolkit/json.h>

#include <cstdlib>    // EXIT_SUCCESS
#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <ios>        // std::ios_base, std::ios::binary
#include <iostream>   // std::cin, std::cout
#include <istream>    // std::basic_istream

template <typename CharT, typename Traits>
static auto decode_from_stream(sourcemeta::jsontoolkit::JSON &schema,
                               std::basic_istream<CharT, Traits> &stream)
    -> int {
  sourcemeta::jsonbinpack::Canonicalizer canonicalizer{
      sourcemeta::jsonbinpack::cli::resolver};
  canonicalizer.apply(schema, sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);
  sourcemeta::jsonbinpack::Mapper mapper{
      sourcemeta::jsonbinpack::cli::resolver};
  mapper.apply(schema, sourcemeta::jsonbinpack::DEFAULT_METASCHEMA);
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
  std::ifstream schema_stream{schema_path, std::ios::binary};
  std::ifstream data_stream{data_path, std::ios::binary};
  schema_stream.exceptions(std::ios_base::badbit);
  data_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(schema_stream)};
  return decode_from_stream(schema, data_stream);
}

auto sourcemeta::jsonbinpack::cli::decode(
    const std::filesystem::path &schema_path) -> int {
  std::ifstream schema_stream{schema_path, std::ios::binary};
  schema_stream.exceptions(std::ios_base::badbit);
  sourcemeta::jsontoolkit::JSON schema{
      sourcemeta::jsontoolkit::parse(schema_stream)};
  return decode_from_stream(schema, std::cin);
}
