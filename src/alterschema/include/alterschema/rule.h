#ifndef SOURCEMETA_ALTERSCHEMA_RULE_H_
#define SOURCEMETA_ALTERSCHEMA_RULE_H_

#include <jsontoolkit/json.h>

#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <utility>       // std::move

namespace sourcemeta::alterschema {
class Rule {
public:
  Rule(std::string name) : name_{std::move(name)} {}

  // Necessary to wrap rules on smart pointers
  virtual ~Rule() = default;

  // We don't need any of these
  Rule(const Rule &) = delete;
  Rule(Rule &&) = delete;
  auto operator=(const Rule &) -> Rule & = delete;
  auto operator=(Rule &&) -> Rule & = delete;

  auto operator==(const Rule &other) const -> bool;
  auto operator!=(const Rule &other) const -> bool;
  [[nodiscard]] auto name() const -> const std::string &;
  auto apply(sourcemeta::jsontoolkit::JSON &document,
             sourcemeta::jsontoolkit::Value &value, const std::string &dialect,
             const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool;

private:
  [[nodiscard]] virtual auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &dialect,
            const std::unordered_map<std::string, bool> &vocabularies) const
      -> bool = 0;
  virtual auto transform(sourcemeta::jsontoolkit::JSON &document,
                         sourcemeta::jsontoolkit::Value &value) const
      -> void = 0;
  const std::string name_;
};
} // namespace sourcemeta::alterschema

#endif
