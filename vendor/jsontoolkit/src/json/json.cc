#include "parser.h"
#include "stringify.h"

#include <sourcemeta/jsontoolkit/json.h>

#include <fstream> // std::ifstream
#include <ios>     // std::ios_base

namespace sourcemeta::jsontoolkit {

auto parse(std::basic_istream<JSON::Char, JSON::CharTraits> &stream,
           std::uint64_t &line, std::uint64_t &column) -> JSON {
  return parse<JSON::Char, JSON::CharTraits, std::allocator>(stream, line,
                                                             column);
}

auto parse(const std::basic_string<JSON::Char, JSON::CharTraits> &input,
           std::uint64_t &line, std::uint64_t &column) -> JSON {
  return parse<JSON::Char, JSON::CharTraits, std::allocator>(input, line,
                                                             column);
}

auto parse(std::basic_istream<JSON::Char, JSON::CharTraits> &stream) -> JSON {
  std::uint64_t line{1};
  std::uint64_t column{0};
  return parse<JSON::Char, JSON::CharTraits, std::allocator>(stream, line,
                                                             column);
}

auto parse(const std::basic_string<JSON::Char, JSON::CharTraits> &input)
    -> JSON {
  std::uint64_t line{1};
  std::uint64_t column{0};
  return parse<JSON::Char, JSON::CharTraits, std::allocator>(input, line,
                                                             column);
}

auto from_file(const std::filesystem::path &path) -> JSON {
  std::ifstream stream{path};
  stream.exceptions(std::ios_base::badbit);
  return parse(stream);
}

auto stringify(const JSON &document,
               std::basic_ostream<JSON::Char, JSON::CharTraits> &stream)
    -> void {
  stringify<JSON::Char, JSON::CharTraits, std::allocator>(document, stream);
}

auto prettify(const JSON &document,
              std::basic_ostream<JSON::Char, JSON::CharTraits> &stream)
    -> void {
  prettify<JSON::Char, JSON::CharTraits, std::allocator>(document, stream);
}

auto operator<<(std::basic_ostream<JSON::Char, JSON::CharTraits> &stream,
                const JSON &document)
    -> std::basic_ostream<JSON::Char, JSON::CharTraits> & {
#ifdef NDEBUG
  stringify(document, stream);
#else
  prettify(document, stream);
#endif
  return stream;
}

} // namespace sourcemeta::jsontoolkit
