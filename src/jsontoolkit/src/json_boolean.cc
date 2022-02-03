#include <jsontoolkit/json_value.h>
#include <jsontoolkit/json_boolean.h>
#include <stdexcept>

static const char * const JSON_TRUE = "true";
static const char * const JSON_FALSE = "false";

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericBoolean<Wrapper>::GenericBoolean()
  : source{JSON_FALSE}, must_parse{false}, data{false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericBoolean<Wrapper>::GenericBoolean(const bool value)
  : source{value ? JSON_TRUE : JSON_FALSE}, must_parse{false}, data{value} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericBoolean<Wrapper>::GenericBoolean(const std::string_view &document)
  : source{document}, must_parse{true}, data{false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericBoolean<Wrapper>& sourcemeta::jsontoolkit::GenericBoolean<Wrapper>::parse() {
  if (this->must_parse) {
    // TODO: Handle whitespace, etc correctly
    if (this->source == "false") {
      this->set(false);
    } else if (this->source == "true") {
      this->set(true);
    } else {
      throw std::domain_error("Invalid document");
    }
  }

  this->must_parse = false;
  return *this;
}

template <typename Wrapper>
bool sourcemeta::jsontoolkit::GenericBoolean<Wrapper>::value() {
  return this->parse().data;
}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericBoolean<Wrapper>&
sourcemeta::jsontoolkit::GenericBoolean<Wrapper>::set(const bool value) {
  // Updating the value negates the source
  this->must_parse = false;
  this->data = value;
  return *this;
}

template <typename Wrapper>
sourcemeta::jsontoolkit::Type sourcemeta::jsontoolkit::GenericBoolean<Wrapper>::type() const {
  return this->data
    ? sourcemeta::jsontoolkit::Type::True
    : sourcemeta::jsontoolkit::Type::False;
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>::GenericBoolean();
template sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>::GenericBoolean(const bool);
template sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>::GenericBoolean(const std::string_view&);

template sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>&
sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>::parse();
template bool sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>::value();

template sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>&
sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>::set(const bool);

template sourcemeta::jsontoolkit::Type
sourcemeta::jsontoolkit::GenericBoolean<sourcemeta::jsontoolkit::JSON>::type() const;
