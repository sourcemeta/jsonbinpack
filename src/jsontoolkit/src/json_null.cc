#include <jsontoolkit/json_value.h>
#include <jsontoolkit/json_null.h>
#include <stdexcept>

static const char * const JSON_NULL = "null";

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericNull<Wrapper>::GenericNull()
  : source{JSON_NULL}, must_parse{false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericNull<Wrapper>::GenericNull(const std::string_view &document)
  : source{document}, must_parse{true} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericNull<Wrapper>& sourcemeta::jsontoolkit::GenericNull<Wrapper>::parse() {
  if (this->must_parse && this->source != "null") {
    throw std::domain_error("Invalid document");
  }

  this->must_parse = false;
  return *this;
}

template <typename Wrapper>
sourcemeta::jsontoolkit::Type sourcemeta::jsontoolkit::GenericNull<Wrapper>::type() const {
  return sourcemeta::jsontoolkit::Type::Null;
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericNull<sourcemeta::jsontoolkit::JSON>::GenericNull();
template sourcemeta::jsontoolkit::GenericNull<sourcemeta::jsontoolkit::JSON>::GenericNull(const std::string_view&);

template sourcemeta::jsontoolkit::GenericNull<sourcemeta::jsontoolkit::JSON>&
sourcemeta::jsontoolkit::GenericNull<sourcemeta::jsontoolkit::JSON>::parse();

template sourcemeta::jsontoolkit::Type
sourcemeta::jsontoolkit::GenericNull<sourcemeta::jsontoolkit::JSON>::type() const;
