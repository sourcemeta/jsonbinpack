#ifndef SOURCEMETA_ALTERSCHEMA_RULE_H_
#define SOURCEMETA_ALTERSCHEMA_RULE_H_

#include <jsontoolkit/json.h>
#include <string> // std::string

namespace sourcemeta::alterschema {
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
  auto apply(sourcemeta::jsontoolkit::JSON<std::string> &value) const -> bool;

private:
  [[nodiscard]] virtual auto
  condition(const sourcemeta::jsontoolkit::JSON<std::string> &schema) const
      -> bool = 0;
  virtual auto
  transform(sourcemeta::jsontoolkit::JSON<std::string> &value) const
      -> void = 0;
  const std::string _name;
};
} // namespace sourcemeta::alterschema

#endif
