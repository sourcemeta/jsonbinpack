#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_RULE_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_RULE_H_

#include <jsontoolkit/json.h>
#include <string> // std::string

namespace sourcemeta::jsonbinpack::canonicalizer {
class Rule {
public:
  Rule(std::string name);
  virtual auto condition(const sourcemeta::jsontoolkit::JSON &value)
      -> bool = 0;
  virtual auto transform(sourcemeta::jsontoolkit::JSON &value) -> void = 0;
  [[nodiscard]] auto name() const -> const std::string &;
  auto operator()(sourcemeta::jsontoolkit::JSON &value)
      -> sourcemeta::jsontoolkit::JSON &;

private:
  const std::string _name;
};
} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
