#include <jsontoolkit/json_internal.h>
#include <jsontoolkit/json_null.h>
#include <stdexcept> // std::domain_error

auto sourcemeta::jsontoolkit::Null::stringify() -> std::string {
  return std::string{sourcemeta::jsontoolkit::Null::token_constant};
}

auto sourcemeta::jsontoolkit::Null::parse(std::istream &input)
    -> std::nullptr_t {
  sourcemeta::jsontoolkit::internal::flush_whitespace(input);
  std::size_t index{0};
  const auto size = sourcemeta::jsontoolkit::Null::token_constant.size();

  while (!input.eof()) {
    const char character = static_cast<char>(input.get());

    if (index < size) {
      if (sourcemeta::jsontoolkit::Null::token_constant.at(index) !=
          character) {
        throw std::domain_error("Invalid null");
      }
    } else if (character != EOF) {
      throw std::domain_error("Invalid end of null");
    }

    index++;
  }

  return nullptr;
}
