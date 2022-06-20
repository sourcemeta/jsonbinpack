#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <jsontoolkit/schema.h>

#include <algorithm> // std::copy_if
#include <iterator>  // std::next, std::make_move_iterator

namespace sourcemeta::jsonbinpack::canonicalizer::rules {

class DuplicateAllOfBranches final
    : public sourcemeta::jsonbinpack::canonicalizer::Rule {
public:
  DuplicateAllOfBranches() : Rule("duplicate_allof_branches"){};
  [[nodiscard]] auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool override {
    if (!sourcemeta::jsontoolkit::schema::has_vocabulary<std::string>(
            schema, "https://json-schema.org/draft/2020-12/vocab/applicator") ||
        !schema.is_object() || !schema.defines("allOf") ||
        !schema.at("allOf").is_array()) {
      return false;
    }

    // We can't use std::unique given JSON documents
    // cannot be "sorted" in any deterministic manner.
    const auto &branches = schema.at("allOf").to_array();
    for (auto iterator = branches.cbegin(); iterator != branches.cend();
         ++iterator) {
      for (auto subiterator = std::next(iterator, 1);
           subiterator != branches.cend(); ++subiterator) {
        if (subiterator != iterator && *subiterator == *iterator) {
          return true;
        }
      }
    }

    return false;
  }

  auto transform(sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> void override {
    std::vector<sourcemeta::jsontoolkit::JSON<std::string>> new_branches{};
    auto &branches = schema.at("allOf").to_array();
    std::copy_if(std::make_move_iterator(std::begin(branches)),
                 std::make_move_iterator(std::end(branches)),
                 std::back_inserter(new_branches), [&](const auto &branch) {
                   return std::find(std::begin(new_branches),
                                    std::end(new_branches),
                                    branch) == std::end(new_branches);
                 });

    schema.assign("allOf", new_branches);
  }
};

} // namespace sourcemeta::jsonbinpack::canonicalizer::rules
