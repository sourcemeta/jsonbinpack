#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_RULES_UTILS_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_RULES_UTILS_H_

#include <algorithm> // std::any_of, std::copy_if
#include <set>       // std::set
#include <string>    // std::string

#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

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
