#include <sourcemeta/jsontoolkit/jsonl.h>

namespace sourcemeta::jsontoolkit {

JSONL::JSONL(std::basic_istream<JSON::Char, JSON::CharTraits> &stream)
    : data{stream} {}

auto JSONL::begin() -> JSONL::const_iterator { return {&this->data}; }
auto JSONL::end() -> JSONL::const_iterator { return {nullptr}; }
auto JSONL::cbegin() -> JSONL::const_iterator { return {&this->data}; }
auto JSONL::cend() -> JSONL::const_iterator { return {nullptr}; }

} // namespace sourcemeta::jsontoolkit
