#include <jsontoolkit/json.h>
#include <jsontoolkit/json_object.h>
#include <stdexcept> // std::domain_error

#include "utils.h"

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericObject<Wrapper>::GenericObject()
    : Container{
          std::string{
              sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin} +
              std::string{
                  sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end},
          false} {}

template <typename Wrapper>
sourcemeta::jsontoolkit::GenericObject<Wrapper>::GenericObject(
    const std::string_view &document)
    : Container{document, true} {}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::size() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::size_type {
  this->parse();
  return this->data.size();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::contains(
    const typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::key_type
        &key) -> bool {
  return this->data.find(key) != this->data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::at(
    const typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::key_type
        &key) & ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::mapped_type & {
  this->parse();
  return this->data.at(key);
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::at(
    const typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::key_type
        &key) && ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::mapped_type {
  this->parse();
  return std::move(this->data.at(key));
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::parse_source() -> void {
  const std::string_view document{
      sourcemeta::jsontoolkit::utils::trim(this->source())};
  if (document.front() !=
          sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_begin ||
      document.back() !=
          sourcemeta::jsontoolkit::GenericObject<Wrapper>::token_end) {
    throw std::domain_error("Invalid object");
  }
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::begin() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::iterator {
  this->parse();
  return this->data.begin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::end() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::iterator {
  this->parse();
  return this->data.end();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cbegin() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  this->parse();
  return this->data.cbegin();
}

template <typename Wrapper>
auto sourcemeta::jsontoolkit::GenericObject<Wrapper>::cend() ->
    typename sourcemeta::jsontoolkit::GenericObject<Wrapper>::const_iterator {
  this->parse();
  return this->data.cend();
}

// Explicit instantiation

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::GenericObject();
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::GenericObject(const std::string_view &);

template typename sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::size_type
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::size();

template bool
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::contains(
    const std::string_view &);

template typename sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::mapped_type &
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::at(
    const typename sourcemeta::jsontoolkit::GenericObject<
        sourcemeta::jsontoolkit::JSON>::key_type &key) &;

template typename sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::mapped_type
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::at(
    const typename sourcemeta::jsontoolkit::GenericObject<
        sourcemeta::jsontoolkit::JSON>::key_type &key) &&;

template void sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::parse_source();

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::begin();
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::end();

template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::cbegin();
template sourcemeta::jsontoolkit::GenericObject<
    sourcemeta::jsontoolkit::JSON>::const_iterator
sourcemeta::jsontoolkit::GenericObject<sourcemeta::jsontoolkit::JSON>::cend();
