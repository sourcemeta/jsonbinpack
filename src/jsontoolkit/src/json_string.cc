#include <string>
#include <jsontoolkit/json_value.h>
#include <jsontoolkit/json_string.h>

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::GenericString()
  : source{"\"\""}, must_parse{false}, data{""} {}

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::GenericString(const std::string_view &document)
  : source{document}, must_parse{true} {}

template <typename Wrapper, typename Backend>
typename sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::size_type
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::size() {
  return this->parse().data.size();
}

template <typename Wrapper, typename Backend>
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>&
sourcemeta::jsontoolkit::GenericString<Wrapper, Backend>::parse() {
  if (this->must_parse) {
    //
  }

  this->must_parse = false;
  return *this;
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::GenericString();
template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::GenericString(const std::string_view&);

template typename sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::size_type
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::size();

template sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>&
sourcemeta::jsontoolkit::GenericString<sourcemeta::jsontoolkit::JSON, std::string>::parse();
