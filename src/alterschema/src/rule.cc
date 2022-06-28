#include <alterschema/rule.h>
#include <stdexcept>
#include <utility> // std::move

sourcemeta::alterschema::Rule::Rule(std::string name)
    : _name{std::move(name)} {}

auto sourcemeta::alterschema::Rule::name() const -> const std::string & {
  return this->_name;
}

auto sourcemeta::alterschema::Rule::apply(
    sourcemeta::jsontoolkit::JSON<std::string> &value) const -> bool {

  // A rule cannot be applied to a non-parsed JSON value given
  // that the condition operates on a constant document
  value.parse();

  if (this->condition(value)) {
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

  return false;
}
