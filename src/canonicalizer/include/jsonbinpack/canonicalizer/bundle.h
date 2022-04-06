#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_BUNDLE_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_BUNDLE_H_

#include <jsonbinpack/canonicalizer/rule.h>
#include <jsontoolkit/json.h>
#include <memory> // std::unique_ptr
#include <vector> // std::vector

namespace sourcemeta::jsonbinpack::canonicalizer {
class Bundle {
public:
  Bundle() = default;
  auto add(std::unique_ptr<sourcemeta::jsonbinpack::canonicalizer::Rule> &&rule)
      -> void;
  auto apply(sourcemeta::jsontoolkit::JSON &document)
      -> sourcemeta::jsontoolkit::JSON &;

private:
  std::vector<std::unique_ptr<sourcemeta::jsonbinpack::canonicalizer::Rule>>
      rules;
};
} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
