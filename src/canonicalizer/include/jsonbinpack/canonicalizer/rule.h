#ifndef SOURCEMETA_JSONBINPACK_CANONICALIZER_RULE_H_
#define SOURCEMETA_JSONBINPACK_CANONICALIZER_RULE_H_

#include <jsontoolkit/json.h>
#include <string> // std::string

namespace sourcemeta::jsonbinpack::canonicalizer {
class Rule {
public:
  Rule(std::string name);

  // Necessary to wrap rules on smart pointers
  virtual ~Rule() = default;

  // We don't need any of these
  Rule(const Rule &) = delete;
  Rule(Rule &&) = delete;
  auto operator=(const Rule &) -> Rule & = delete;
  auto operator=(Rule &&) -> Rule & = delete;

  [[nodiscard]] auto name() const -> const std::string &;
  auto apply(sourcemeta::jsontoolkit::JSON &value) -> bool;

private:
  [[nodiscard]] virtual auto
  condition(const sourcemeta::jsontoolkit::JSON &value) const -> bool = 0;
  virtual auto transform(sourcemeta::jsontoolkit::JSON &value) -> void = 0;
  const std::string _name;
};
} // namespace sourcemeta::jsonbinpack::canonicalizer

#endif
