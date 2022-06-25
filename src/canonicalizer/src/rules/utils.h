#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_RULES_UTILS_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_RULES_UTILS_H_

#include <algorithm> // std::any_of, std::copy_if
#include <iterator>  // std::inserter
#include <set>       // std::set
#include <string>    // std::string
#include <vector>    // std::vector

#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

// We can't use std::unique given JSON documents
// cannot be "sorted" in any deterministic manner.
template <typename S>
// TODO: Can we implement this function obeying
// std::unique iterator-based interface?
// TODO: Can we use std::unique by using std::sort with a custom comparer?
auto unique(sourcemeta::jsontoolkit::JSON<S> &document) -> void {
  std::vector<sourcemeta::jsontoolkit::JSON<S>> new_items{};
  // TODO: Make this work on objects too
  auto &items = document.to_array();
  std::copy_if(std::make_move_iterator(std::begin(items)),
               std::make_move_iterator(std::end(items)),
               std::back_inserter(new_items), [&](const auto &item) {
                 return std::find(std::begin(new_items), std::end(new_items),
                                  item) == std::end(new_items);
               });

  document = new_items;
}

template <typename S>
auto defines_any_keyword_from_set(
    const sourcemeta::jsontoolkit::JSON<S> &schema,
    const std::string &vocabulary, const std::set<S> &keywords) -> bool {
  return sourcemeta::jsontoolkit::schema::has_vocabulary<S>(schema,
                                                            vocabulary) &&
         std::any_of(keywords.cbegin(), keywords.cend(),
                     [&schema](const auto &keyword) {
                       return schema.defines(keyword);
                     });
}

template <typename S, typename OutputIterator>
auto copy_extra_keywords(const sourcemeta::jsontoolkit::JSON<S> &schema,
                         const std::string &vocabulary,
                         const std::set<S> &keywords, OutputIterator output)
    -> void {
  if (sourcemeta::jsontoolkit::schema::has_vocabulary<S>(schema, vocabulary)) {
    std::copy_if(
        keywords.cbegin(), keywords.cend(), output,
        [&schema](const auto &keyword) { return schema.defines(keyword); });
  }
}

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules

#endif
