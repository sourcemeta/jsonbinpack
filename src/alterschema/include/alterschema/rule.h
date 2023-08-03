#ifndef SOURCEMETA_ALTERSCHEMA_RULE_H_
#define SOURCEMETA_ALTERSCHEMA_RULE_H_

#include <jsontoolkit/json.h>

#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <utility>       // std::move

namespace sourcemeta::alterschema {
class Rule {
public:
  /// Create an Alterschema rule. Each rule must have a unique name.
  Rule(std::string name) : name_{std::move(name)} {}

  // Necessary to wrap rules on smart pointers
  virtual ~Rule() = default;

  // We don't need any of these
  Rule(const Rule &) = delete;
  Rule(Rule &&) = delete;
  auto operator=(const Rule &) -> Rule & = delete;
  auto operator=(Rule &&) -> Rule & = delete;

  /// Compare an Alterschema rule against another rule.
  auto operator==(const Rule &other) const -> bool;

  /// Compare an Alterschema rule against another rule.
  auto operator!=(const Rule &other) const -> bool;

  /// Fetch the name of an Alterschema rule
  [[nodiscard]] auto name() const -> const std::string &;

  /// Apply the Alterschema rule to a JSON document
  auto apply(sourcemeta::jsontoolkit::JSON &document,
             sourcemeta::jsontoolkit::Value &value, const std::string &draft,
             const std::unordered_map<std::string, bool> &vocabularies,
             const std::size_t level) const -> bool;

private:
  /// The rule condition
  [[nodiscard]] virtual auto
  condition(const sourcemeta::jsontoolkit::Value &schema,
            const std::string &draft,
            const std::unordered_map<std::string, bool> &vocabularies,
            const std::size_t level) const -> bool = 0;

  /// The rule transformation
  virtual auto transform(sourcemeta::jsontoolkit::JSON &document,
                         sourcemeta::jsontoolkit::Value &value) const
      -> void = 0;
  const std::string name_;
};
} // namespace sourcemeta::alterschema

#endif
