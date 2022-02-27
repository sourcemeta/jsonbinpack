#include "parsers/parser.h"
#include <jsontoolkit/json_string.h>

sourcemeta::jsontoolkit::String::String() : source{"\"\""}, must_parse{false} {}

sourcemeta::jsontoolkit::String::String(const std::string_view &document)
    : source{document}, must_parse{true} {}

auto sourcemeta::jsontoolkit::String::value() -> const std::string & {
  this->parse();
  return this->data;
}

auto sourcemeta::jsontoolkit::String::size() ->
    typename sourcemeta::jsontoolkit::String::size_type {
  this->parse();
  return this->data.size();
}

auto sourcemeta::jsontoolkit::String::parse() -> void {
  if (this->must_parse) {
    this->data = sourcemeta::jsontoolkit::parser::string(this->source);
    this->must_parse = false;
  }
}

auto sourcemeta::jsontoolkit::String::begin() ->
    typename sourcemeta::jsontoolkit::String::iterator {
  this->parse();
  return this->data.begin();
}

auto sourcemeta::jsontoolkit::String::end() ->
    typename sourcemeta::jsontoolkit::String::iterator {
  this->parse();
  return this->data.end();
}

auto sourcemeta::jsontoolkit::String::cbegin() ->
    typename sourcemeta::jsontoolkit::String::const_iterator {
  this->parse();
  return this->data.cbegin();
}

auto sourcemeta::jsontoolkit::String::cend() ->
    typename sourcemeta::jsontoolkit::String::const_iterator {
  this->parse();
  return this->data.cend();
}

auto sourcemeta::jsontoolkit::String::rbegin() ->
    typename sourcemeta::jsontoolkit::String::reverse_iterator {
  this->parse();
  return this->data.rbegin();
}

auto sourcemeta::jsontoolkit::String::rend() ->
    typename sourcemeta::jsontoolkit::String::reverse_iterator {
  this->parse();
  return this->data.rend();
}

auto sourcemeta::jsontoolkit::String::crbegin() ->
    typename sourcemeta::jsontoolkit::String::const_reverse_iterator {
  this->parse();
  return this->data.crbegin();
}

auto sourcemeta::jsontoolkit::String::crend() ->
    typename sourcemeta::jsontoolkit::String::const_reverse_iterator {
  this->parse();
  return this->data.crend();
}
