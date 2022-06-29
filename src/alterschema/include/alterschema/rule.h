#ifndef SOURCEMETA_ALTERSCHEMA_RULE_H_
#define SOURCEMETA_ALTERSCHEMA_RULE_H_

#include <jsontoolkit/json.h>

#include <stdexcept> // std:runtime_error
#include <string>    // std::string
#include <utility>   // std::move

namespace sourcemeta::alterschema {
template <typename Source> class Rule {
public:
  Rule(std::string name) : _name{std::move(name)} {}

  // Necessary to wrap rules on smart pointers
  virtual ~Rule() = default;

  // We don't need any of these
  Rule(const Rule &) = delete;
  Rule(Rule &&) = delete;
  auto operator=(const Rule &) -> Rule & = delete;
  auto operator=(Rule &&) -> Rule & = delete;

  auto operator==(const Rule<Source> &other) const -> bool {
    return this->name() == other.name();
  }

  inline auto operator!=(const Rule<Source> &other) const -> bool {
    return !this->operator==(other);
  }

  [[nodiscard]] auto name() const -> const std::string & { return this->_name; }

  auto apply(sourcemeta::jsontoolkit::JSON<Source> &value) const -> bool {
    // A rule cannot be applied to a non-parsed JSON value given
    // that the condition operates on a constant document
    value.parse();

    if (!this->condition(value)) {
      return false;
    }

    this->transform(value);
    value.parse();

    // The condition must always be false after applying the
    // transformation in order to avoid infinite loops
    if (this->condition(value)) {
      throw std::runtime_error(
          "A rule condition must not hold after applying the rule");
    }

    return true;
  }

private:
  [[nodiscard]] virtual auto
  condition(const sourcemeta::jsontoolkit::JSON<Source> &schema) const
      -> bool = 0;
  virtual auto transform(sourcemeta::jsontoolkit::JSON<Source> &value) const
      -> void = 0;
  const std::string _name;
};
} // namespace sourcemeta::alterschema

#endif
