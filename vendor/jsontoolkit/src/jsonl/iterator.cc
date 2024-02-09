#include <sourcemeta/jsontoolkit/jsonl_iterator.h>

#include "grammar.h"

#include <cassert> // assert

namespace sourcemeta::jsontoolkit {

struct ConstJSONLIterator::Internal {
  sourcemeta::jsontoolkit::JSON current;
};

/*
 * Parsing
 */

auto ConstJSONLIterator::parse_next() -> JSON {
  if (this->data && !this->data->eof()) {
    return parse(*this->data, this->line, this->column);
  } else {
    // Just as a cheap placeholder
    return JSON{nullptr};
  }
}

auto ConstJSONLIterator::operator++() -> ConstJSONLIterator & {
  assert(this->data);

start:
  switch (this->data->get()) {
    // Separator
    case internal::token_jsonl_line_feed<JSON::Char>:
      this->line += 1;
      this->column = 0;
      goto element;

    // Whitespace
    case internal::token_jsonl_whitespace_space<JSON::Char>:
    case internal::token_jsonl_whitespace_tabulation<JSON::Char>:
    case internal::token_jsonl_whitespace_carriage_return<JSON::Char>:
      this->column += 1;
      goto start;

    case JSON::CharTraits::eof():
      goto end;
    default:
      this->column += 1;
      throw ParseError(this->line, this->column);
  }

element:
  switch (this->data->peek()) {
    // Whitespace
    case internal::token_jsonl_whitespace_space<JSON::Char>:
    case internal::token_jsonl_whitespace_tabulation<JSON::Char>:
    case internal::token_jsonl_whitespace_carriage_return<JSON::Char>:
      this->column += 1;
      this->data->ignore(1);
      goto element;

    case JSON::CharTraits::eof():
      goto end;
    default:
      goto next;
  }

next:
  this->internal->current = this->parse_next();
  return *this;

end:
  this->data = nullptr;
  return *this;
}

/*
 * Miscellaneous
 */

ConstJSONLIterator::ConstJSONLIterator(
    std::basic_istream<JSON::Char, JSON::CharTraits> *stream)
    : data{stream}, internal{new Internal({this->parse_next()})} {}

ConstJSONLIterator::~ConstJSONLIterator() {}

auto operator==(const ConstJSONLIterator &left, const ConstJSONLIterator &right)
    -> bool {
  return (!left.data && !right.data) ||
         (left.data && right.data &&
          left.internal->current == right.internal->current);
};

auto ConstJSONLIterator::operator*() const -> ConstJSONLIterator::reference {
  assert(this->data);
  return this->internal->current;
}

auto ConstJSONLIterator::operator->() const -> ConstJSONLIterator::pointer {
  assert(this->data);
  return &(this->internal->current);
}

} // namespace sourcemeta::jsontoolkit
