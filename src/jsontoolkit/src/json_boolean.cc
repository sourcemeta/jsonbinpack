#include <jsontoolkit/json_boolean.h>
#include <jsontoolkit/json_internal.h>

#include <stdexcept> // std::domain_error

auto sourcemeta::jsontoolkit::Boolean::stringify(std::ostream &output,
                                                 const bool value) -> void {
  if (value) {
    output << sourcemeta::jsontoolkit::Boolean::token_constant_true;
  } else {
    output << sourcemeta::jsontoolkit::Boolean::token_constant_false;
  }
}

auto sourcemeta::jsontoolkit::Boolean::parse(std::istream &input) -> bool {
  const auto size_false =
      sourcemeta::jsontoolkit::Boolean::token_constant_false.size();
  const auto size_true =
      sourcemeta::jsontoolkit::Boolean::token_constant_true.size();

  sourcemeta::jsontoolkit::internal::flush_whitespace(input);

  std::size_t index{0};
  bool result = false;

  while (!input.eof()) {
    const char character = static_cast<char>(input.get());

    if (index == 0) {
      if (character ==
          sourcemeta::jsontoolkit::Boolean::token_constant_false.front()) {
        result = false;
      } else if (character ==
                 sourcemeta::jsontoolkit::Boolean::token_constant_true
                     .front()) {
        result = true;
      } else {
        throw std::domain_error("Invalid boolean");
      }
    } else if (result) {
      if (index < size_true) {
        if (sourcemeta::jsontoolkit::Boolean::token_constant_true.at(index) !=
            character) {
          throw std::domain_error("Invalid truthy boolean");
        }
      } else if (character != EOF &&
                 !sourcemeta::jsontoolkit::internal::is_blank(character)) {
        throw std::domain_error("Invalid end of truthy boolean");
      }
    } else {
      if (index < size_false) {
        if (sourcemeta::jsontoolkit::Boolean::token_constant_false.at(index) !=
            character) {
          throw std::domain_error("Invalid falsy boolean");
        }
      } else if (character != EOF &&
                 !sourcemeta::jsontoolkit::internal::is_blank(character)) {
        throw std::domain_error("Invalid end of falsy boolean");
      }
    }

    index++;
  }

  return result;
}
